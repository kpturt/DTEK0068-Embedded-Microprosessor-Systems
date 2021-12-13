/* 
 * File:   adc.c
 * Author: Kari-Pekka Turtiainen / kpturt@utu.fi
 *
 * Created on 12 December 2021, 14:53
 */

#include <avr/io.h>
#include "FreeRTOS.h"
#include <semphr.h> //For mutex
#include "../W07E01_LCD.X/FreeRTOS/Source/adc.h"
#include "uart.h"

// Function that reads the LDR value
uint16_t ldr_read(void)
{
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
    return ADC0.RES; // Read and return LDR value
}

// Function that reads the NTC value
uint16_t ntc_read(void)
{ 
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
    return ADC0.RES; // Read and return NTC value
}

// Function that reads the PM value
uint16_t pm_read(void)
{  
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
    return ADC0.RES; // Read and return PM value
}

// Function to read and set adc values, protected by mutex
ADC_result_t read_adc_values()
{
    ADC_result_t adc_result;
    xSemaphoreTake(mutex_handle, 100); // Take mutex
    adc_result.ldr = ldr_read();
    adc_result.ntc = ntc_read();
    adc_result.pm = pm_read();
    xSemaphoreGive(mutex_handle); // Give mutex
    return adc_result;
}