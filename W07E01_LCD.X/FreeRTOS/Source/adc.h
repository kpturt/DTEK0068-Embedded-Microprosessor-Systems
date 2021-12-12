/* 
 * File:   adc.h
 * Author: Kari-Pekka Turtiainen / kpturt@utu.fi
 *
 * Created on 12 December 2021, 14:53
 */

#ifndef ADC_H
#define	ADC_H
#include "FreeRTOSConfig.h"
#include "semphr.h"

SemaphoreHandle_t mutex_handle;

void adc_init(void);
typedef struct {
    uint16_t pm;
    uint16_t ldr;
    uint16_t ntc;
}ADC_result_t;

ADC_result_t read_adc_values();

uint16_t pm_read(void);
uint16_t ldr_read(void);
uint16_t ntc_read(void);

#endif	/* ADC_H */

