/* 
 * File:   dummy.c
 * Author: Kari-Pekka Turtiainen / kpturt@utu.fi
 *
 * Created on 12 December 2021, 17:48
 */

#include <avr/io.h> 
#include <stdio.h>
#include <stdlib.h>
#include "FreeRTOS.h"
#include "clock_config.h"
#include "semphr.h"
#include "timers.h"
#include "../W07E01_LCD.X/FreeRTOS/Source/adc.h"
#include "task.h"
#include "dummy.h"

// Function for led timer callback
void led_timer_callback()
{
    ADC_result_t adc_result = read_adc_values(); // Read ADC
    
    // If NTC value is greater than PM value, turn led on
    if(adc_result.ntc > adc_result.pm)
    {
        // Set on board LED on
        PORTF.OUTCLR = PIN5_bm;
    }
    else
    {
        // Set on board LED off
        PORTF.OUTSET = PIN5_bm;
    }
}

// Function for dummy task
void dummy_task(void *parameters)
{
    PORTF.DIRSET = PIN5_bm; // Sets PF5 (LED) as output (1)
    
    // Create timer for LED
    TimerHandle_t led_timer = xTimerCreate(
        "led",
        100, // once every 100 ms
        pdTRUE, // Timer expires with set frequency
        ( void * ) 5,
        led_timer_callback
    );
    
    xTimerStart(led_timer, 0);
    
    vTaskDelay(200); // 200 ms delay before superloop
    
    for(;;)
    {
        ;
    }
    
    // Above loop will not end, but as a practice, tasks should always include
    // a vTaskDelete() call just-in-case
    vTaskDelete(NULL);
}