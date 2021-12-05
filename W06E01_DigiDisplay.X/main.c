/*
 * File:   main.c
 * Author: Kari-Pekka Turtiainen / kpturt@utu.fi
 *
 * Created on December 5, 2021, 8:49 PM
 * 
 * This program does the following: When the device receives an input digit from
 * 0-9 from the terminal, it displays it on the seven segment display and informs
 * the user that it is a digit. If the received message is not a digit, it shows
 * an error and displays the letter "E" on the seven segment display.
 */

#include <avr/io.h>
// Given in the course example
#include "FreeRTOS.h"
#include "clock_config.h"
#include "task.h"
// From USART guide
#include "queue.h"
#include <string.h>
#include <xc.h>

#define USART0_BAUD_RATE(BAUD_RATE) \
((float)(3333333 * 64 / (16 * (float)BAUD_RATE)) + 0.5) // From USART guide

// 7-segment values from 0 to 9 in an array + E and empty
uint8_t seven_segment_numbers[] =
{   
    0b00111111, // 0
    0b00000110,
    0b01011011,
    0b01001111,
    0b01100110,
    0b01101101,
    0b01111101,
    0b00000111,
    0b01111111,
    0b01100111, // 9
    0b01111001, // E
    0b00000000, // empty
};

// Initialize queues
volatile static QueueHandle_t xqueue_number, xqueue_message;

// Function to display numbers on the seven segment display
void seven_segment(void* parameter)
{
    PORTC.DIRSET = 0xFF; // Sets PORTC (LED display) ports as outputs (1)
    PORTF.DIRSET = PIN5_bm; // Drive PF5 (Transistor) as output (1) and ground
    PORTF.OUTSET = PIN5_bm; // and also drive display to ground
    
    uint8_t seven_segment_index = 11; // Initialize index to show empty
    char nr_que_msg; // Temporary char to save received number queue message
    
    // This task will run indefinitely
    for (;;)
    {
        // Check if there is a character in number queue
        if(xQueueReceive(xqueue_number, (void*) & nr_que_msg, 0) == pdTRUE )
        {
            if(nr_que_msg == '0')
            {
                seven_segment_index = 0;
            }
            else if(nr_que_msg == '1')
            {
                seven_segment_index = 1;
            }
            else if(nr_que_msg == '2')
            {
                seven_segment_index = 2;
            }
            else if(nr_que_msg == '3')
            {
                seven_segment_index = 3;
            }
            else if(nr_que_msg == '4')
            {
                seven_segment_index = 4;
            }
            else if(nr_que_msg == '5')
            {
                seven_segment_index = 5;
            }
            else if(nr_que_msg == '6')
            {
                seven_segment_index = 6;
            }
            else if(nr_que_msg == '7')
            {
                seven_segment_index = 7;
            }
            else if(nr_que_msg == '8')
            {
                seven_segment_index = 8;
            }
            else if(nr_que_msg == '9')
            {
                seven_segment_index = 9;
            }
            else
            {
                seven_segment_index = 10; // Else display E for error
            }
            // And sets the index set from queue number to seven segment
            PORTC.OUT = seven_segment_numbers[seven_segment_index];
        }
    }
    // Above loop will not end, but as a practice, tasks should always include
    // a vTaskDelete() call just-in-case
    vTaskDelete(NULL);
}

// Function to create and initialize queue
void create_queue(void)
{
    const uint8_t number_queue_length = 10; // Number queue length
    const uint8_t message_queue_length = 10; // Message queue length
    // Create queue for numbers
    xqueue_number = xQueueCreate(number_queue_length, sizeof(uint8_t));
    // Create queue for messages
    xqueue_message = xQueueCreate(message_queue_length, sizeof(uint8_t));
}

// Function to initialize USART0, from Microship USART guide
void USART0_init(void)
{
    PORTA.DIRSET = PIN0_bm; // Set PA0 as output (1)
    PORTA.DIRCLR = PIN1_bm; // Set PA1 as input (0)
    // For setting baud to 9600
    USART0.BAUD = (uint16_t)USART0_BAUD_RATE(9600);
    // For enabling transmitter and receiver
    USART0.CTRLB |= USART_RXEN_bm | USART_TXEN_bm;
}

// Function to send chars to terminal, from Microship USART guide
void USART0_sendChar(char c)
{
    while (!(USART0.STATUS & USART_DREIF_bm))
    {
        ;
    }        
    USART0.TXDATAL = c;
}

// Function to send strings to terminal, from Microship USART guide
void USART0_sendString(char *str)
{
    for(size_t i = 0; i < strlen(str); i++)
    {
        USART0_sendChar(str[i]);
    }
}

// Function to read terminal, from Microship USART guide
uint8_t USART0_read()
{
    while (!(USART0.STATUS & USART_RXCIF_bm))
    {
        ;
    }
    return USART0.RXDATAL;
}

// Function to send messages to terminal
void send_message(void* parameter)
{
    char que_msg; // Temporary char to save message from message queue
    
    // This task will run indefinitely
    for(;;)
    {  
        // This checks if there are messages in queue
        if(xQueueReceive(xqueue_message,
                (void *)&que_msg, 0) == pdTRUE) 
        {
            // Here we check if the given input is number or not
            if(que_msg >= '0' && que_msg <= '9')
            {
                // If number, give confirmation
                USART0_sendString("Valid digit!\r\n");
            }
            else
            { 
                // If not a number, give error
                USART0_sendString("Error! Not a valid digit.\r\n");
            }
        }
    }
    // Above loop will not end, but as a practice, tasks should always include
    // a vTaskDelete() call just-in-case
    vTaskDelete(NULL);
}

// Function to receive messages from terminal
void receive_message(void* parameter)
{   
    char rec_msg; // Temporary char to save received message from USRT0
    // This task will run indefinitely
    for(;;)
    {
        // Read and save received message to the char
        rec_msg = USART0_read();
        // Send to number queue
        xQueueSend(xqueue_number, (void *)&rec_msg, 10);
        // Send to message queue
        xQueueSend(xqueue_message, (void *)&rec_msg, 10);
    }
    // Above loop will not end, but as a practice, tasks should always include
    // a vTaskDelete() call just-in-case
    vTaskDelete(NULL);
}


int main(void)
{
    create_queue(); // Create and initialize queue
    USART0_init(); // Initialize USART0
    
    // Create a task for seven segment display
    xTaskCreate(
        seven_segment,
        "segment",
        configMINIMAL_STACK_SIZE,
        NULL,
        tskIDLE_PRIORITY,
        NULL
    );
    
    // Create a task for sending messages
    xTaskCreate(
        send_message,
        "send_msg",
        configMINIMAL_STACK_SIZE,
        NULL,
        tskIDLE_PRIORITY,
        NULL
    );
    
    // Create a task for receiving messages
    xTaskCreate(
        receive_message,
        "receive_msg",
        configMINIMAL_STACK_SIZE,
        NULL,
        tskIDLE_PRIORITY,
        NULL
    );

    // Start the scheduler
    vTaskStartScheduler();

    // Scheduler will not return
    return 0;
}