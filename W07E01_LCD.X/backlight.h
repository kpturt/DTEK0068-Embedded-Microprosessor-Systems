/* 
 * File:   backlight.h
 * Author: Kari-Pekka Turtiainen / kpturt@utu.fi
 *
 * Created on 12 December 2021, 16:15
 */

#ifndef BACKLIGHT_H
#define	BACKLIGHT_H

#ifdef	__cplusplus
extern "C" {
#endif

// Function declarations
void tcb_init(void);
void backlight_timer_callback();
void timeout_timer_callback();
void backlight_task(void *parameters);
// Declarations
ADC_result_t adc_result;
uint16_t last_pm_value;
uint16_t current_pm_value;

#ifdef	__cplusplus
}
#endif

#endif	/* BACKLIGHT_H */

