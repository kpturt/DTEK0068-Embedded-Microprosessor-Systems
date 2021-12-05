/* 
 * File:   main.c
 * Author: Kari-Pekka Turtiainen / kpturt@utu.fi
 *
 * Created on 14 November 2021, 05:42
 * Target device: ATmega4809 Curiosity Nano
 * 
 * This program does the following:
 * upon startup, spins a line around the 7-segment LED display.
 */

#define F_CPU  3333333   // For delay, sets 3.33 MHz clock frequency
#include <util/delay.h>
#include <avr/io.h> 

// 7-segment values for each line
uint8_t seven_segment_numbers[] =
{   
    0b0100000, //f
    0b0010000, //e
    0b0001000, //d
    0b0000100, //c
    0b0000010, //b
    0b0000001, //a
};

int main(void) 
{ 
    PORTC.DIRSET = 0xFF; // Sets PORTC (LED display) ports as outputs (1)
    uint8_t index = 5; // Display starts from number 9 
    
    // Main superloop
    while (1)
    {
        // Changes display to a number marked by index of array
        PORTC.OUT = seven_segment_numbers[index];
        
        if(index == 0){
            index = 6;
        }
        index -= 1;
        _delay_ms(50);
    }
}

