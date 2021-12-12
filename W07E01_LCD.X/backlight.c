#include <avr/io.h>
#include "FreeRTOS.h"
#include "task.h"
#include "../W07E01_LCD.X/FreeRTOS/Source/adc.h"
#include "timers.h"

ADC_result_t adc_result;
uint16_t last_pm;
TimerHandle_t backlight_time;

void backlight_timer_callback()
{
    uint16_t ratio = adc_result.ldr*10/1023;
    TCB3.CCMP = 0xFFFF - (0xFFFF/10*ratio);
}
void timeout_timer_callback()
{
    if(xTimerIsTimerActive(backlight_time) == pdTRUE)
    {
        xTimerStop(backlight_time, 0);
    }
    TCB3.CCMP = 0;
}

void backlight_task(void *parameters)
{
    backlight_time = xTimerCreate(
        "backlight",
        100,
        pdTRUE,
        ( void * ) 3,
        backlight_timer_callback
    );
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
        xSemaphoreTake(mutex_handle, 100);
        adc_result = read_adc_values();
        xSemaphoreGive(mutex_handle);
        
        if(last_pm == adc_result.pm)
        {
            if(xTimerIsTimerActive(timeout_time) == pdFALSE)
            {
                xTimerStart(timeout_time, 0);
            }
        }
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

void backlight_init()
{
    PORTB.DIRSET = PIN5_bm;
    PORTB.OUTSET = PIN5_bm;
}