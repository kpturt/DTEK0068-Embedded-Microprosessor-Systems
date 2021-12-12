/* 
 * File:   uart.h
 * Author: Kari-Pekka Turtiainen / kpturt@utu.fi
 *
 * Created on 12 December 2021, 13:06
 */

#ifndef USART_H
#define	USART_H

// Setting baud rate
#define USART0_BAUD_RATE(BAUD_RATE) \
((float)(configCPU_CLOCK_HZ * 64 / (16 * (float)BAUD_RATE)) + 0.5)

// Initialize functions
void usart_init(void);
void usart_send_char(char c);
void usart_send_string(char *str);
void usart_task(void* parameters);

#endif	/* USART_H */