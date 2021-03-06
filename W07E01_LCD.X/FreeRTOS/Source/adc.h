/* 
 * File:   adc.h
 * Author: Kari-Pekka Turtiainen / kpturt@utu.fi
 *
 * Created on 12 December 2021, 14:53
 */

#ifndef ADC_H
#define	ADC_H
#include "FreeRTOS.h"
#include "semphr.h"

// Declare result data types
typedef struct
{
    uint16_t ldr;
    uint16_t ntc;
    uint16_t pm;
}ADC_result_t;

// Declarations
void adc_init(void);
uint16_t ldr_read(void);
uint16_t ntc_read(void);
uint16_t pm_read(void);
ADC_result_t read_adc_values();
SemaphoreHandle_t mutex_handle;

#endif	/* ADC_H */

