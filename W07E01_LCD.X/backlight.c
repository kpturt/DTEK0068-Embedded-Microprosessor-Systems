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

// Initialisations
ADC_result_t adc_result;
uint16_t last_pm;
TimerHandle_t backlight_time;

// Function for backlight timer callback
void backlight_timer_callback()
{
    uint16_t ratio = adc_result.ldr*10/1023;
    TCB3.CCMP = 0xFFFF - (0xFFFF/10*ratio);
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
        100,
        pdTRUE,
        ( void * ) 3,
        backlight_timer_callback
    );
    // Timer for timeout
    TimerHandle_t timeout_time = xTimerCreate(
        "timeout",
        10000,
        pdFALSE,
        ( void * ) 4, 
        timeout_timer_callback
    );
    xTimerStart(backlight_time, 0);
    
    vTaskDelay(200);
    
    for(;;)
    {
        xSemaphoreTake(mutex_handle, 100); // Take mutex
        adc_result = read_adc_values(); // Read adc values
        xSemaphoreGive(mutex_handle); // Give mutex
        
        // If pm value equals and timeout is not on, start timeout
        if(last_pm == adc_result.pm)
        {
            if(xTimerIsTimerActive(timeout_time) == pdFALSE)
            {
                xTimerStart(timeout_time, 0);
            }
        }
        /* Else if backoutlight is not on, start it
         * or if timer is on, stop it
         */
        else{
            if(xTimerIsTimerActive(backlight_time) == pdFALSE)
            {
                xTimerStart(backlight_time, 0);
            }
            if(xTimerIsTimerActive(timeout_time) == pdTRUE)
            {
                xTimerStop(timeout_time,0);
            }
            last_pm = adc_result.pm;
        }
    }
    
    // Above loop will not end, but as a practice, tasks should always include
    // a vTaskDelete() call just-in-case
    vTaskDelete(NULL);
}