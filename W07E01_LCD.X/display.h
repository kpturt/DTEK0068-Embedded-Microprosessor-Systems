/* 
 * File:   display.h
 * Author: kptur
 *
 * Created on 12 December 2021, 17:19
 */

#ifndef DISPLAY_H
#define	DISPLAY_H

#ifdef	__cplusplus
extern "C" {
#endif

void display_task(void *parameters);
QueueHandle_t lcd_queue;

#ifdef	__cplusplus
}
#endif

#endif	/* DISPLAY_H */

