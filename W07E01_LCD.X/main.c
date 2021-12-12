/* 
 * File:   main.c
 * Author: Kari-Pekka Turtiainen / kpturt@utu.fi
 *
 * Created on 09 December 2021, 22:36
 * 
 * This program does the following:
 * 
 */

#include <avr/io.h>

// Given in the course example
#include "FreeRTOS.h"
#include "semphr.h"
#include "clock_config.h"
#include "task.h"

// From USART guide
#include "queue.h"
#include <string.h>
#include <xc.h>
#include <stdio.h>

#include <semphr.h>//For mutex
#include <avr/interrupt.h> // For interrupts and sei() + cli() (not needed?)
#include <avr/cpufunc.h> // To enable CCP register change (not needed?)

#include "uart.h"
#include "../W07E01_LCD.X/FreeRTOS/Source/adc.h"
#include "lcd.h"
#include "backlight.h"
#include "display.h"
#include "dummy.h"

// Initialise functions
void clock_init (void);
void tcb_init (void);

SemaphoreHandle_t mutex_handle; // Global mutex

// Function to intialise clock, probably not needed
void clock_init(void)
{
    //Enable writing to protected register
    CPU_CCP = CCP_IOREG_gc;
    // Enable prescaler, set PDIV to 64 divider
    CLKCTRL.MCLKCTRLB = CLKCTRL_PDIV_64X_gc | CLKCTRL_PEN_bm;
    //Enable writing to protected register
    CPU_CCP = CCP_IOREG_gc;
    // Select OSCULP32K and set to 0x1 value
    CLKCTRL.MCLKCTRLA = CLKCTRL_CLKSEL_OSCULP32K_gc;
    
    // Wait for the oscillator to finish
    while (CLKCTRL.MCLKSTATUS & CLKCTRL_SOSC_bm)
    {
        ;
    }
}

// Function to initialise TCB3
void tcb_init(void)
{
    //Set PB5 as output
    PORTB_DIR |= PIN5_bm;
    PORTB_OUT |= PIN5_bm;
    
    TCB3.CCMP = 0x80FF; // Enable to generate 8bit PWM signal
    TCB3.CTRLA |= TCB_ENABLE_bm; // Enable TCB3
    // Divide CLK_PER by 2 to get lowest frequency
    TCB3.CTRLA |= TCB_CLKSEL_CLKDIV2_gc;
    TCB3.CTRLB |= TCB_CCMPEN_bm; // Enable pin output
    TCB3.CTRLB |= TCB_CNTMODE_PWM8_gc; // Configure TCB to 8 bit mode
}

int main(void)
{
    // Create mutex before starting tasks
    mutex_handle = xSemaphoreCreateMutex();
    usart_init(); // Initialise USART
    tcb_init(); // Initialise TCB3
    
    lcd_queue = xQueueCreate(1, sizeof(ADC_result_t));
    
    PORTB.DIRSET = PIN5_bm; // Sets PORTC (LCD) ports as outputs (1)
    PORTB.OUTSET = PIN5_bm; // Sets PORTC (LCD) ports as outputs (1)
    PORTF.DIRCLR = PIN4_bm; // Set PF4 (PM) as input (0)
    PORTE.DIRCLR = PIN0_bm; // Set PE0 (LDR) as input (0)
    PORTE.DIRCLR = PIN1_bm; // Set PE1 (NTC) as input (0)
    
    // PE0 (LDR) No pull-up, no invert, disable input buffer
    PORTE.PIN0CTRL = PORT_ISC_INPUT_DISABLE_gc;
    // PE1 (NTC) No pull-up, no invert, disable input buffer
    PORTE.PIN1CTRL = PORT_ISC_INPUT_DISABLE_gc;
    // PF4 (PM) No pull-up, no invert, disable input buffer
    PORTF.PIN4CTRL = PORT_ISC_INPUT_DISABLE_gc;
    
    // Set Port A internal reference voltage to 2.5
    VREF.CTRLA |= VREF_ADC0REFSEL_2V5_gc;
    // Clear REFSEL
    ADC0.CTRLC &= ~(ADC_REFSEL_VDDREF_gc);
    // Set Port C internal reference voltage to 2.5
    ADC0.CTRLC |= ADC_REFSEL_INTREF_gc;
    
    // Enable (power up) ADC (10-bit resolution is default)
    ADC0.CTRLA |= ADC_ENABLE_bm;
    // Set prescaler to 16
    ADC0.CTRLC |= ADC_PRESC_DIV16_gc;
    

    // For printing to serial
    xTaskCreate( 
        usart_task, 
        "print", 
        configMINIMAL_STACK_SIZE, 
        NULL, 
        tskIDLE_PRIORITY, 
        NULL 
    );
    
    // For LCD task
    xTaskCreate(
        lcd_task,
        "lcd",
        configMINIMAL_STACK_SIZE, 
        NULL, 
        tskIDLE_PRIORITY, 
        NULL    
    );
    
    // For backlight task
    xTaskCreate(
        backlight_task,
        "backlight",
        configMINIMAL_STACK_SIZE, 
        NULL, 
        tskIDLE_PRIORITY, 
        NULL    
    );
    
    // For display task
    xTaskCreate(
        display_task,
        "display",
        configMINIMAL_STACK_SIZE, 
        NULL, 
        tskIDLE_PRIORITY, 
        NULL
    );
    
    // For dummy task
    xTaskCreate( 
        dummy_task, 
        "dummy", 
        configMINIMAL_STACK_SIZE, 
        NULL, 
        tskIDLE_PRIORITY,  // Should have high priority, like 20
        NULL 
    ); 
    
    // Start the scheduler 
     vTaskStartScheduler(); 
     // Scheduler will not return 
     return 0; 
}