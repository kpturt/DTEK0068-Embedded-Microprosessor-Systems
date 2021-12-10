/* 
 * File:   main.c
 * Author: Kari-Pekka Turtiainen / kpturt@utu.fi
 *
 * Created on 09 December 2021, 22:36
 */

#include <avr/io.h>
// Given in the course example
#include "FreeRTOS.h"
#include "clock_config.h"
#include "task.h"
// From USART guide
#include "queue.h"
#include <string.h>
#include <xc.h>
#include <stdio.h>
//For mutex
#include <semphr.h>

#define F_CPU 3333333
// Defining constants that are required for serial communication
#define USART0_BAUD_RATE(BAUD_RATE) \
((float)(F_CPU * 64 / (16 * (float)BAUD_RATE)) + 0.5)

void USART1_init(void);
void USART1_sendChar(char c);
void USART1_sendString(char *str);
uint16_t pm_read(void);

static SemaphoreHandle_t mutex;

//------------------------------------------------------------------------------
// Function to initialize USART0, from Microship USART guide
void USART0_init(void)
{
    PORTA.DIRSET = PIN0_bm; // Set PA0 as output (1)
    PORTA.DIRCLR = PIN1_bm; // Set PA1 as input (0) not needed?
    // For setting baud to 9600
    USART0.BAUD = (uint16_t)USART0_BAUD_RATE(9600);
    // For enabling transmitter
    USART0.CTRLB |= USART_TXEN_bm;
}
// Function to send chars to terminal, from Microship USART guide
void USART0_sendChar(char c)
{
    while (!(USART0.STATUS & USART_DREIF_bm))
    {
        ;
    }        
    USART0.TXDATAL = c;
}
// Function to send strings to terminal, from Microship USART guide
void USART0_sendString(char *str)
{
    for(size_t i = 0; i < strlen(str); i++)
    {
        USART0_sendChar(str[i]);
    }
}
// Function to read terminal, from Microship USART guide
uint8_t USART0_read()
{
    while (!(USART0.STATUS & USART_RXCIF_bm))
    {
        ;
    }
    return USART0.RXDATAL;
}//-----------------------------------------------------------------------------

// Function that reads the PM value
uint16_t pm_read(void)
{
    // Take the mutex
    xSemaphoreTake(mutex, portMAX_DELAY);
    
    ADC0.CTRLC |= ADC_REFSEL_INTREF_gc; // Set reference voltage to VDD (5V)
    ADC0.MUXPOS = ADC_MUXPOS_AIN14_gc; // // MUXPOS to read AIN14 = PF4 (PM)
    // Start conversion (bit cleared when conversion is done) 
    ADC0.COMMAND = ADC_STCONV_bm;
    // When the conversion is done, the RESRDY bit in the ADC0.INTFLAGS
    // gets set by the hardware. Without interrupt handler, the program
    // must wait for that bit to get set before reading the ADC result.
    while (!(ADC0.INTFLAGS & ADC_RESRDY_bm))
    {
        ;
    }
    
    // Release the mutex so that the creating function can finish
    xSemaphoreGive(mutex);
    
    return ADC0.RES; // Read and return PM value
}

// Function that reads the LDR value
uint8_t ldr_read(void)
{
    // Take the mutex
    xSemaphoreTake(mutex, portMAX_DELAY);
    
    ADC0.CTRLC &= ~ADC_REFSEL_VDDREF_gc; // Clear REFSEL
    ADC0.CTRLC |= ADC_REFSEL_VDDREF_gc; // Set reference voltage to (2.5V)
    ADC0.MUXPOS = ADC_MUXPOS_AIN8_gc; // MUXPOS to read AIN8 = PE0 (LDR))
    // Start conversion (bit cleared when conversion is done)
    ADC0.COMMAND = ADC_STCONV_bm;
    // When the conversion is done, the RESRDY bit in the ADC0.INTFLAGS 
    // gets set by the hardware. Without interrupt handler, the program 
    // must wait for that bit to get set before reading the ADC result. 
    while (!(ADC0.INTFLAGS & ADC_RESRDY_bm)) 
    { 
        ; 
    }
    
    // Release the mutex so that the creating function can finish
    xSemaphoreGive(mutex);
    
    return ADC0.RES; // Read and return LDR value
}

// Function that reads the LDR value
uint8_t ntc_read(void)
{
    // Take the mutex
    xSemaphoreTake(mutex, portMAX_DELAY);
    
    ADC0.CTRLC &= ~ADC_REFSEL_VDDREF_gc; // Clear REFSEL
    ADC0.CTRLC |= ADC_REFSEL_VDDREF_gc; // Set reference voltage to (2.5V)
    ADC0.MUXPOS = ADC_MUXPOS_AIN9_gc; // MUXPOS to read AIN9 = PE1 (LDR))
    // Start conversion (bit cleared when conversion is done)
    ADC0.COMMAND = ADC_STCONV_bm;
    // When the conversion is done, the RESRDY bit in the ADC0.INTFLAGS 
    // gets set by the hardware. Without interrupt handler, the program 
    // must wait for that bit to get set before reading the ADC result. 
    while (!(ADC0.INTFLAGS & ADC_RESRDY_bm)) 
    { 
        ; 
    }
    
    // Release the mutex so that the creating function can finish
    xSemaphoreGive(mutex);
    
    return ADC0.RES; // Read and return NTC value
}

// Function to print to 
void print(void *parameters) 
{ 
    uint16_t pm_value; // Value for the potentiometer read;
    char pm_value_string[800];
    uint16_t ldr_value; // Value for the potentiometer read;
    char ldr_value_string[800];
    uint16_t ntc_value; // Value for the potentiometer read;
    char ntc_value_string[800];
    
    // This task will run indefinitely
    for (;;)
    {
        pm_value = pm_read();
        ldr_value = ldr_read();
        ntc_value = ntc_read();
        sprintf(pm_value_string, "PM value: (%d) ", pm_value);
        sprintf(ldr_value_string, "LDR value: (%d) ", ldr_value);
        sprintf(ntc_value_string, "NTC value: (%d)", ntc_value);
        USART0_sendString("\n\rValues - ");
        USART0_sendString(pm_value_string);
        USART0_sendString(ldr_value_string);
        USART0_sendString(ntc_value_string);
        vTaskDelay(1000 / portTICK_PERIOD_MS); //1000ms or 1 second delay
    }
    // Above loop will not end, but as a practice, tasks should always include
    // a vTaskDelete() call just-in-case
    vTaskDelete(NULL);
}

int main(void)
{
    USART0_init(); // Initialize USRT0
    TCB3.CTRLB |= TCB_CCMPEN_bm; // Enable TCB
    TCB3.CTRLB |= TCB_CNTMODE_PWM8_gc; // Configure TCB to 8 bit PWM mode
    PORTD.DIRSET = 0xFF; // Sets PORTC (LED display) ports as outputs (1)
    PORTF.DIRCLR = PIN4_bm; // Set PF4 (PM) as input (0)
    PORTE.DIRCLR = PIN0_bm; // Set PE0 (LDR) as input (0)
    PORTE.DIRCLR = PIN1_bm; // Set PE1 (NTC) as input (0)
    
    // PE0 (LDR) No pull-up, no invert, disable input buffer
    PORTE.PIN0CTRL = PORT_ISC_INPUT_DISABLE_gc;
    // PE1 (NTC) No pull-up, no invert, disable input buffer
    PORTE.PIN1CTRL = PORT_ISC_INPUT_DISABLE_gc;
    // PF4 (PM) No pull-up, no invert, disable input buffer
    PORTF.PIN4CTRL = PORT_ISC_INPUT_DISABLE_gc;
    
    // Internal reference voltage to 2.5
    //VREF.CTRLA |= VREF_ADC0REFSEL_2V5_gc;
    //Kumpi ??
    // Use Vdd as reference voltage and set prescaler of 16 
    ADC0.CTRLC |= ADC_PRESC_DIV16_gc | ADC_REFSEL_VDDREF_gc;
    
    // Enable (power up) ADC (10-bit resolution is default)
    ADC0.CTRLA |= ADC_ENABLE_bm;
    
    // Create mutex before starting tasks
    mutex = xSemaphoreCreateMutex();

    // For printing to serial
    xTaskCreate( 
         print, 
         "print", 
         configMINIMAL_STACK_SIZE, 
         NULL, 
         tskIDLE_PRIORITY, 
         NULL 
    );
    
    // Start the scheduler 
     vTaskStartScheduler(); 
     // Scheduler will not return 
     return 0; 
}