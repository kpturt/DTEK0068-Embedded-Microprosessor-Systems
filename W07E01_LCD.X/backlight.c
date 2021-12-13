/* 
 * File:   backlight.c
 * Author: Kari-Pekka Turtiainen / kpturt@utu.fi
 *
 * Created on 12 December 2021, 16:15
 */

#include <avr/io.h>
#include "FreeRTOS.h"
#include "task.h"
#include "../W07E01_LCD.X/FreeRTOS/Source/adc.h"
#include "timers.h"
#include "backlight.h"

// Timer handle declarations
TimerHandle_t backlight_time;
TimerHandle_t timeout_time;

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

// Function for backlight timer callback, monitors backlight brightness by ldr
void backlight_timer_callback()
{
    uint16_t ratio = (adc_result.ldr*10)/1023;
    TCB3.CCMP = 0x7fff/10*ratio; // 0x7ff half maximum value ? 32.768
}

// Function for timeout timer callback
void timeout_timer_callback()
{
    if(xTimerIsTimerActive(backlight_time) == pdTRUE)
    {
        xTimerStop(backlight_time, 0);
    }
    TCB3.CCMP = 0;
}

// Function for backlight task
void backlight_task(void *parameters)
{
    // Timer for backlight time
    backlight_time = xTimerCreate(
        "backlight",
        100, // 1/10 -> 10 times a second
        pdTRUE, // Timer expires with set frequency
        ( void * ) 3,
        backlight_timer_callback // function call for timer expire
    );
    
    // Timer for screen blackout countdown
    TimerHandle_t timeout_time = xTimerCreate(
        "timeout",
        20000, // 10 seconds timeout for backlight
        pdFALSE, // Timer is oneshot and will enter dormant when expires
        ( void * ) 4, 
        timeout_timer_callback // function call for timer expire
    );
    
    xTimerStart(backlight_time, 0);
    
    last_pm_value = 0; // Initialise pm value
    
    vTaskDelay(200); // 200 ms delay before superloop
    
    for(;;)
    {
        adc_result = read_adc_values(); // Read adc values
        current_pm_value = adc_result.pm; // Write current pm value
            
        /* If pm value not changed, start 10 second timeout countdown
         * equals "==" cannot be used since pm value is not stable.*/
        if(last_pm_value <= current_pm_value+20 \
        && last_pm_value >= current_pm_value-20)
        {
            if(xTimerIsTimerActive(timeout_time) == pdFALSE)
            {
                xTimerStart(timeout_time, 0);
            }   
        }
            
        // If value changed, wake up the display
        else
        {
            if(xTimerIsTimerActive(backlight_time) == pdFALSE)
            {
                xTimerStart(backlight_time, 0);
            }
            if(xTimerIsTimerActive(timeout_time) == pdTRUE)
            {
                xTimerStop(timeout_time,0);
            }
        }
        
        vTaskDelay(50); // Small delay for the pm change to be noticed
        last_pm_value = current_pm_value; // Write current pm value as last
    }
    
    // Above loop will not end, but as a practice, tasks should always include
    // a vTaskDelete() call just-in-case
    vTaskDelete(NULL);
}