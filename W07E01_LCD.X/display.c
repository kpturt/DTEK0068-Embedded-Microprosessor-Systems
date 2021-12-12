/* 
 * File:   display.c
 * Author: kptur
 *
 * Created on 12 December 2021, 17:17
 */
#include <stdio.h>
#include <stdlib.h>
#include "FreeRTOS.h" 
#include "clock_config.h" 
#include "task.h"
#include "../W07E01_LCD.X/FreeRTOS/Source/adc.h"
#include "display.h"
#include "uart.h"

void display_task(void *parameters)
{
    ADC_result_t adc_results;
    
    vTaskDelay(200);
    
    for(;;)
    {
        xSemaphoreTake(mutex_handle, 100);
        adc_results = read_adc_values();
        xQueueOverwrite(lcd_queue, &adc_results);
        xSemaphoreGive(mutex_handle);
        vTaskDelay(100);
    }
    
    // Above loop will not end, but as a practice, tasks should always include
    // a vTaskDelete() call just-in-case
    vTaskDelete(NULL);
}