/* 
 * File:   main.c
 * Author: kptur
 *
 * Created on 03 November 2021, 22:43
 * 
 * value inverter test
 */

#define F_CPU 3333333

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// global increment variable
uint8_t g_running = 1;
    
int main(void)
{
    // array containing numbers 0-9 and blank for seven segment display
    uint8_t seven_segment_numbers[] =
    {
        0b00111111, 0b00000110, 0b01011011, 
        0b01001111, 0b01100110, 0b01101101, 
        0b01111101, 0b00000111, 0b01111111, 
        0b01100111, 0b00000000
    };
    
    // set PORTC as output
    PORTC.DIRSET = 0xFF;
    
    // set PA4 as input
    PORTA.DIRCLR = PIN4_bm;
    // enable internal pull-up resistor for PA4
    // trigger interrupts on falling edge
    PORTA.PIN4CTRL = PORT_PULLUPEN_bm | PORT_ISC_FALLING_gc;

    //starting countdown from number 9
    uint8_t index = 9;
    // enable interrupts
    sei();
    while (1)
    {
        // display number on seven segment display
        PORTC.OUT = seven_segment_numbers[index];
        
        if(index == 10)
        {
            // set index to zero to display number 0
            index = 0;
        }
        else if(index > 0)
        {
            // decrease numbers amount of g_running
            index -= g_running;
        }
        else
        {
            // set index to ten to clear display
            index = 10;
        }
        // 1 second delay
        _delay_ms(1000);
    }
}

ISR(PORTA_PORT_vect)
{
// clear interrupt flags
PORTA.INTFLAGS = 0xFF;
// set increment to 0 to halt countdown
g_running = 0;

}