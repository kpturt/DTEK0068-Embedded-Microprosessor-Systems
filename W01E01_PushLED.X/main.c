/*
 * File:   main.c
 * Author: Kari-Pekka Turtiainen / kpturt@utu.fi
 *
 * Created on October 30, 2021, 7:00 PM
 * 
 * This program does the following: When the device's button is pressed,
 * it turns the device's LED on.
 */

//for delay
//#define F_CPU   3333333
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
    // Set PIN5 (LED) as output (1).
    PORTF.DIR |= PIN5_bm;
    // Set PIN6 (button) as input (0), not needed thought.
    PORTF.DIR &= ~PIN6_bm;

    // The superloop
    while (1)
    {
        //checks if button is up (high/1)
        if(PORTF.IN & PIN6_bm)
        {
            //sets led off (high/1)
            PORTF.OUT |= PIN5_bm;
        }
        else
        {
            //sets led on (low/0)
            PORTF.OUT &= ~PIN5_bm;
        }
    }
}
