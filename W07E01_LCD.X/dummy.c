/* 
 * File:   dummy.c
 * Author: kptur
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

void led_timer_callback()
{
    xSemaphoreTake(mutex_handle, 100);
    ADC_result_t adc_result = read_adc_values();
    xSemaphoreGive(mutex_handle);
    if(adc_result.ntc > adc_result.pm)
    {
        PORTF.OUTSET = PIN5_bm;
    }
    else
    {
        PORTF.OUTCLR = PIN5_bm;
    }
}

void dummy_task(void *parameters)
{
    PORTF.DIRSET = PIN5_bm;
    TimerHandle_t led_timer = xTimerCreate(
        "led",
        100,
        pdTRUE,
        ( void * ) 5,
        led_timer_callback
    );
    
    xTimerStart(led_timer, 0);
    vTaskDelay(200);
    
    for(;;)
    {
        ;
    }
    
    // Above loop will not end, but as a practice, tasks should always include
    // a vTaskDelete() call just-in-case
    vTaskDelete(NULL);
}