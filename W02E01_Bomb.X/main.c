/* 
 * File:   main.c
 * Author: Kari-Pekka Turtiainen / kpturt@utu.fi
 *
 * Created on 04 November 2021, 22:37
 * Target device: ATmega4809 Curiosity Nano
 * 
 * This program does the following: When powered up the device starts counting
 * down from 9 to 0. If the timer reaches zero the device "explodes", meaning
 * that the display starts blinking the value 0.
 * If the red wire is "cut" (removed) before the timer reaches zero,
 * the countdown stops and the program becomes halted.
 */

#define F_CPU  3333333   // For delay, sets 3.33 MHz clock frequency 
#include <avr/io.h> 
#include <util/delay.h> 
#include <avr/interrupt.h> // For interrupts and sei() + cli()

// Global variable (volatile!), 1 = TRUE and running, 0 = FALSE and halted
volatile uint8_t g_running = 1;

// 7-segment values from 0 to 9 in an array + first one being "empty"
uint8_t seven_segment_numbers[] =
{   
    0b00000000, // empty
    0b00111111, // 0
    0b00000110,
    0b01011011,
    0b01001111,
    0b01100110,
    0b01101101,
    0b01111101,
    0b00000111,
    0b01111111,
    0b01100111 // 9
};
 
int main(void) 
{ 
    PORTC.DIRSET = 0xFF; // Sets PORTC (LED display) ports as outputs (1)
    PORTA.DIRCLR = PIN4_bm; // Sets PORTA (stopper/red wire) pin 4 as input (0)
    uint8_t index = 10; // Display starts from number 9 
    
    /*If the wire in PORTA pin 4 loses connection to the ground,
     *internal pull-up resistor wins and PA4 input becomes HIGH and
     *triggers an interrupt due to a rising edge. 
     *PULLUPEN = enable bit mask, RISING = rising edge*/
    PORTA.PIN4CTRL = PORT_PULLUPEN_bm | PORT_ISC_RISING_gc;
    
    // Enables interrupts
    sei();
    
    // Main superloop
    while (1)
    {
        // Executes loop when FALSE
        while(!g_running)
        {
            /* Do nothing, program halted with this loop.
             * Could also be simplified as: 
             * while(!g_running);
             * but the use of braces is a good practise.
             */
        };
        
        // Changes display to a number marked by index of array
        PORTC.OUT = seven_segment_numbers[index];
        
        /*When timer reaches index 1 (zero), go into a new indefinite superloop
         *and blink the screen between zero and empty.*/
        if(index < 2)
        {   
            while(1){
                PORTC.OUT = seven_segment_numbers[0]; // Set to empty
                _delay_ms(100); // Tenth of a second delays for blinking
                PORTC.OUT = seven_segment_numbers[1]; // Set to zero
                _delay_ms(100);
            }
        }
        
        _delay_ms(1000); // One second delay for countdown
        index -= 1; // Decrement index which affects the displayed number
    }
}

ISR(PORTA_PORT_vect)
{
    // Clears interrupt flag(s) by writing 1 over the module
    PORTA.INTFLAGS = 0xFF;
    // When an interrupt happens stop the main superloop via global variable
    g_running = 0;
}