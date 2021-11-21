/* 
 * File:   main.c
 * Author: Kari-Pekka Turtiainen / kpturt@utu.fi
 *
 * Created on 20 November 2021, 11:17
 * Target device: ATmega4809 Curiosity Nano
 * 
 * This program does the following: This program was designed to play the
 * light mode version of the "Chrome Dino game". 
 * When the LDR detects change in light (a cactus), it makes the 
 * servo move tapping the space bar and making the dino jump. The PM value
 * changes the sensitivity of the LDR and displays the PM value on the display.
 */

#define F_CPU  3333333   // For delay, sets 3.33 MHz clock frequency 
#include <util/delay.h>
#include <avr/io.h>

// Macros for servo control
#define SERVO_PWM_PERIOD        (0x1046) 
#define SERVO_PWM_DUTY_NEUTRAL  (0x0138)
#define SERVO_PWM_DUTY_MAX      (0x00D0)

// 7-segment values from 0 to A (10) in an array
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
    0b01110111 // A
};

uint16_t LDR_value = 0; // Value for the the LDR read
uint16_t PM_value = 0; // Value for the potentiometer read
uint8_t digit_index = 0; // Display number index

uint8_t ldr_read(void)
{
    ADC0.CTRLC &= ~ADC_REFSEL_VDDREF_gc; // Clear REFSEL
    ADC0.CTRLC |= ADC_REFSEL_VDDREF_gc; // Set reference voltage to (2.5V)
    ADC0.MUXPOS = ADC_MUXPOS_AIN8_gc; // MUXPOS to read AIN8 = PE0 (LDR))
    // Start conversion (bit cleared when conversion is done)
    ADC0.COMMAND = ADC_STCONV_bm;
    // When the conversion is done, the RESRDY bit in the ADC0.INTFLAGS 
    // gets set by the hardware. Without interrupt handler, the program 
    // must wait for that bit to get set before reading the ADC result. 
    while (!(ADC0.INTFLAGS & ADC_RESRDY_bm)) 
    { 
        ; 
    }
    LDR_value = ADC0.RES / 100; // Read and set LDR value, divide by 100 
}

 uint8_t pm_read(void)
{
    ADC0.CTRLC |= ADC_REFSEL_INTREF_gc; // Set reference voltage to VDD (5V)
    ADC0.MUXPOS = ADC_MUXPOS_AIN14_gc; // // MUXPOS to read AIN14 = PF4 (PM)
    // Start conversion (bit cleared when conversion is done) 
    ADC0.COMMAND = ADC_STCONV_bm;
    // When the conversion is done, the RESRDY bit in the ADC0.INTFLAGS 
    // gets set by the hardware. Without interrupt handler, the program 
    // must wait for that bit to get set before reading the ADC result. 
    while (!(ADC0.INTFLAGS & ADC_RESRDY_bm)) 
    { 
        ; 
    }
    PM_value = ADC0.RES / 100; // Read and set PM value, divide by 100
}

int main(void) 
{
    PORTC.DIRSET = 0xFF; // Sets PORTC (LED display) ports as outputs (1)
    PORTE.DIRCLR = PIN0_bm; // Set PE0 (LDR) as input (0)
    PORTF.DIRCLR = PIN4_bm; // Set PF4 (PM) as input (0)
    PORTB.DIRSET = PIN2_bm; // Set PB2 (servo) as digital output (1)
    
    // PE0 No pull-up, no invert, disable input buffer
    PORTE.PIN0CTRL = PORT_ISC_INPUT_DISABLE_gc;
    // PF4 No pull-up, no invert, disable input buffer
    PORTF.PIN4CTRL = PORT_ISC_INPUT_DISABLE_gc;
    
    // Internal reference voltage to 2.5
    VREF.CTRLA |= VREF_ADC0REFSEL_2V5_gc;
    
    // Enable (power up) ADC (10-bit resolution is default)
    ADC0.CTRLA |= ADC_ENABLE_bm; 
    
    // Route TCA0 PWM waveform to PORTB
    PORTMUX.TCAROUTEA |= PORTMUX_TCA0_PORTB_gc;
    // Set TCA0 prescaler value to 16 (~208 kHz) 
    TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV16_gc;
    // Set single-slop PWM generation mode 
    TCA0.SINGLE.CTRLB |= TCA_SINGLE_WGMODE_SINGLESLOPE_gc;
    // Using double-buffering, set PWM period (20 ms) 
    TCA0.SINGLE.PERBUF = SERVO_PWM_PERIOD;
    // Set initial servo arm position as neutral (0 deg) 
    TCA0.SINGLE.CMP2BUF = SERVO_PWM_DUTY_NEUTRAL;
    // Enable Compare Channel 2 
    TCA0.SINGLE.CTRLB |= TCA_SINGLE_CMP2EN_bm;
    // Enable TCA0 peripheral 
    TCA0.SINGLE.CTRLA |= TCA_SINGLE_ENABLE_bm;
    
    // Main superloop
    while(1)
    {   
        ldr_read();
        pm_read();
        /* If LDR value is over the PM value, move the servo position to max,
         * otherwise set servo position to neutral (0 deg.) */
        if(LDR_value < PM_value)
        {
            // Set servo position to neutral
            TCA0.SINGLE.CMP2BUF = SERVO_PWM_DUTY_NEUTRAL;
            // Delay to let the servo do the full movement
            _delay_ms(100);
        }
        else
        {
            // Set servo position to max, press the spacebar
            TCA0.SINGLE.CMP2BUF = SERVO_PWM_DUTY_MAX;
            // Delay to let the servo do the full movement
            _delay_ms(100);
        }
        
        // Changes display to a number representing the PM value
        PORTC.OUT = seven_segment_numbers[PM_value];
        
    }
}
