/* 
 * File:   display.c
 * Author: Kari-Pekka Turtiainen / kpturt@utu.fi
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

// Function for display task
void display_task(void *parameters)
{
    // Initialisations
    ADC_result_t adc_results;
    
    vTaskDelay(200);
    
    for(;;)
    {
        xSemaphoreTake(mutex_handle, 100); // Take mutex
        adc_results = read_adc_values(); // Read adc values
        xQueueOverwrite(lcd_queue, &adc_results); // Add new items to queue
        xSemaphoreGive(mutex_handle); // Give mutex
        vTaskDelay(100);
    }
    
    // Above loop will not end, but as a practice, tasks should always include
    // a vTaskDelete() call just-in-case
    vTaskDelete(NULL);
}