/* 
 * File:   main.c
 * Author: Kari-Pekka Turtiainen / kpturt@utu.fi
 *
 * Created on 04 November 2021, 22:37
 * 
 * This program does the following: When powered up the device starts counting
 * down from 9 to 0. If the timer reaches zero the device "explodes", meaning
 * that the display starts blinking the value 0.
 * If the red wire is "cut" (removed) before the timer reaches zero,
 * the countdown stops.
 */

#define F_CPU  3333333   // for delay, sets 3.33 MHz clock frequency 
#include <avr/io.h> 
#include <util/delay.h> 
#include <avr/interrupt.h> // for sei() and cli()

uint8_t g_running = 1; // global variable
 
int main(void) 
{ 
    // 7 segment values from 0 to 9 in an array + last one being "empty"
    uint8_t seven_segment_numbers[] =
    {
        0b00111111, 0b00000110, 0b01011011, 
        0b01001111, 0b01100110, 0b01101101, 
        0b01111101, 0b00000111, 0b01111111, 
        0b01100111, 0b00000000
    };
    
    PORTC.DIRSET = 0xFF;//set PORTC ports as outputs (1)
    PORTA.DIRCLR = PIN4_bm; //set PORTA pin 4 as input (1))
    uint8_t index = 9; //display starts from number 9 
    
    /*if the wire in PORTA pin 4 is removed, trigger an interrupt
     PULLUPEN = enable bit mask, FALLING = falling edge*/ 
    PORTA.PIN4CTRL = PORT_PULLUPEN_bm | PORT_ISC_FALLING_gc;
    
    //enables interrupts
    sei();
    
    while (1)
    { 
        //changes display to a number marked by index of array
        PORTC.OUT = seven_segment_numbers[index];
        
        /* Own add-on for an added dramatic effect:
         * When the timer reaches zero, this changes the delay to 200ms.
         * The code snippet is specifically in this part of the code to prevent
         * a bug where the wire cut-off gets delayed ( could rather be fixed by
         * cleaning up the code? )
         */
        if(index == 0 || index == 10)
        {
            _delay_ms(200); //fifth of a second delay for "explosion" blinking
        }
        else 
        {
            _delay_ms(1000); //one second delay for countdown
        }
        
        //while the number is not 0 or empty, decrement the index
        if (index < 10 && index > 0) 
        { 
            index -= g_running; //decrements index, thus doing the countdown
        }
        //when timer reaches 0, start blinking the display from 0 to empty
        else if (index == 0) 
        { 
            index += 10; //increments to index 10, "empty"
        }
        else if (index == 10) 
        { 
            index -= 10; //decrements back to index 0, zero
        }
     
    }
}

ISR(PORTA_PORT_vect){
        //clears interrupt flag(s) by writing 1 over the module
        PORTA.INTFLAGS = 0xFF;
        //when interrupt happens, prevent index decrement to stop the timer
        g_running = 0;
    }