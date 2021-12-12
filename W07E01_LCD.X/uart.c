/* 
 * File:   uart.c
 * Author: Kari-Pekka Turtiainen / kpturt@utu.fi
 *
 * Created on 12 December 2021, 13:06
 */

#include <avr/io.h>
#include <string.h>
#include <stdio.h>
#include "FreeRTOS.h" 
#include "clock_config.h" 
#include "task.h" 
#include "queue.h"
#include "uart.h"
#include "../W07E01_LCD.X/FreeRTOS/Source/adc.h"

// Function to initialize USART0, from Microship USART guide
void usart_init(void)
{
    PORTA.DIRSET = PIN0_bm; // Set PA0 as output (1)
    PORTA.DIRCLR = PIN1_bm; // Set PA1 as input (0) not needed?
    // For setting baud to 9600
    USART0.BAUD = (uint16_t)USART0_BAUD_RATE(9600);
    // For enabling transmitter
    USART0.CTRLB |= USART_TXEN_bm;
}
// Function to send chars to terminal, from Microship USART guide
void usart_send_char(char c)
{
    while (!(USART0.STATUS & USART_DREIF_bm))
    {
        ;
    }        
    USART0.TXDATAL = c;
}
// Function to send strings to terminal, from Microship USART guide
void usart_send_string(char *str)
{
    for(size_t i = 0; i < strlen(str); i++)
    {
        usart_send_char(str[i]);
    }
}
// Function to read terminal, from Microship USART guide
uint8_t usart_read()
{
    while (!(USART0.STATUS & USART_RXCIF_bm))
    {
        ;
    }
    return USART0.RXDATAL;
}

// Function to print to terminal
void usart_task(void* parameters) 
{ 
    //uint16_t ldr_value; // Value for the potentiometer read;
    char ldr_value_string[800];
    //uint16_t ntc_value; // Value for the potentiometer read;
    char ntc_value_string[800];
    //uint16_t pm_value; // Value for the potentiometer read;
    char pm_value_string[800];
    
    ADC_result_t output_buffer; // Store value from output queue
    
    vTaskDelay(200);
    
    // This task will run indefinitely
    for (;;)
    {
        xSemaphoreTake(mutex_handle, 100); // Take mutex
        //ldr_value = ldr_read();
        //ntc_value = ntc_read();
        //pm_value = pm_read();
        output_buffer = read_adc_values();
        xSemaphoreGive(mutex_handle); // Give mutex
        
        sprintf(ldr_value_string, "LDR value: (%d) ", output_buffer.ldr);
        sprintf(ntc_value_string, "NTC value: (%d) ", output_buffer.ntc);
        sprintf(pm_value_string, "PM value: (%d) ", output_buffer.pm);
        usart_send_string("\n\rValues - ");
        usart_send_string(ldr_value_string); 
        usart_send_string(ntc_value_string);
        usart_send_string(pm_value_string);
        
       //vTaskDelay(100 / portTICK_PERIOD_MS); //100ms or 1/10 second delay
    }
    // Above loop will not end, but as a practice, tasks should always include
    // a vTaskDelete() call just-in-case
    vTaskDelete(NULL);
}