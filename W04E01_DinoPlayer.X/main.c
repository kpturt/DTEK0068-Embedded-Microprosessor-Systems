/* 
 * File:   main.c
 * Author: Kari-Pekka Turtiainen / kpturt@utu.fi
 *
 * Created on 20 November 2021, 11:17
 * Target device: ATmega4809 Curiosity Nano
 * 
 * This program does the following: This program was designed to play the
 * dark mode version of the "Chrome Dino game". 
 * When the LDR detects change in light (a cactus), it makes the 
 * servo move, tapping the space bar and making the dino jump. The PM value
 * changes the sensitivity of the LDR and displays the PM value on the display.
 */

#include <avr/io.h> 
#include <avr/interrupt.h> // For interrupts and sei() + cli()
#include <avr/cpufunc.h> // To enable CCP register change

// Macros for servo control
#define SERVO_PWM_PERIOD        (0x1046) 
#define SERVO_PWM_DUTY_NEUTRAL  (0x0138)
#define SERVO_PWM_DUTY_MAX      (0x00D0)

// Global variable that checks if the servo should press the space bar
volatile uint8_t g_servo_press = 0;

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

/* 
 * This function is copied and modified from technical brief TB3213  
 * To enable writing to CCP and enable OVF
 */
void rtc_init(void) 
{ 
    uint8_t temp; // Temporary variable to manipulate the register
    // Disable oscillator 
    temp = CLKCTRL.XOSC32KCTRLA; // Copies crystal oscillator register
    temp &= ~CLKCTRL_ENABLE_bm; // Applies bitwise operation (ext osc src off)
            
    // Writing to protected register
    ccp_write_io((void*)&CLKCTRL.XOSC32KCTRLA, temp); 
    // Wait for the clock to be released (0 = unstable, unused) 
    while (CLKCTRL.MCLKSTATUS & CLKCTRL_XOSC32KS_bm); 

    // Select external crystal (SEL = 0) 
    temp = CLKCTRL.XOSC32KCTRLA; 
    temp &= ~CLKCTRL_SEL_bm; 
    ccp_write_io((void*)&CLKCTRL.XOSC32KCTRLA, temp); 

    // Enable oscillator 
    temp = CLKCTRL.XOSC32KCTRLA; 
    temp |= CLKCTRL_ENABLE_bm; 
    ccp_write_io((void*)&CLKCTRL.XOSC32KCTRLA, temp); 
    // Wait for the clock to stabilise 
    while (RTC.STATUS > 0); 

    // Configure RTC module 
    // Select 32.768 kHz external oscillator 
    RTC.CLKSEL = RTC_CLKSEL_TOSC32K_gc; 
    // Enable OVF interrupt 
    RTC.INTCTRL |= RTC_OVF_bm; 
    // Enable RTC and OVF function 
    RTC.CTRLA = RTC_RTCEN_bm;
}

// Function that reads the LDR value
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
    return ADC0.RES / 100; // Read and set LDR value, divide by 100 
}

// Function that reads the PM value
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
    return ADC0.RES / 100; // Read and set PM value, divide by 100
}

int main(void) 
{   
    rtc_init(); // Initialise RTC timer's OVF interrupt function
    
    PORTC.DIRSET = 0xFF; // Sets PORTC (LED display) ports as outputs (1)
    PORTE.DIRCLR = PIN0_bm; // Set PE0 (LDR) as input (0)
    PORTF.DIRCLR = PIN4_bm; // Set PF4 (PM) as input (0)
    PORTB.DIRSET = PIN2_bm; // Set PB2 (servo) as digital output (1)
    
    // PE0 No pull-up, no invert, disable input buffer
    PORTE.PIN0CTRL = PORT_ISC_INPUT_DISABLE_gc;
    // PF4 No pull-up, no invert, disable input buffer
    PORTF.PIN4CTRL = PORT_ISC_INPUT_DISABLE_gc;
    // PB2 No pull-up, no invert, disable input buffer
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
    
    sei(); // Enables interrupts
    
    // Main superloop
    while(1)
    {   
        uint16_t LDR_value = ldr_read(); // Value for the the LDR read
        uint16_t PM_value = pm_read(); // Value for the potentiometer read;
        
        /* If LDR value is over the PM value and the servo is not moving,
         * change the global pressed checker to true and make servo move*/
        if((LDR_value < PM_value) && !g_servo_press)
        {
            g_servo_press = 1; // Change global value and run ISR changes
            while(RTC.STATUS > 0) // Wait for the clock to stabilise
            {
                ;
            }
            RTC.PER = 4096; // set period wait 125ms (~100ms)
        }
        
        // Changes display to a number representing the PM value
        PORTC.OUT = seven_segment_numbers[PM_value]; 
    }
}

//The Interrupt Service Routine (ISR) for the RTC
ISR(RTC_CNT_vect)
{    
   // Clears interrupt flag(s) by writing 1 over the module (RTC_OVF_bm)
    RTC.INTFLAGS = 0xFF;
    
    /* If servo should move (checker is true), move it to max position, 
     * otherwise make the servo position neutral*/
    if(g_servo_press)
    {
        g_servo_press = 0; // Reset press checker
        TCA0.SINGLE.CMP2BUF = SERVO_PWM_DUTY_MAX; // Set servo position to max
    }
    else if(!g_servo_press)
    {
        // If servo is not moving set servo position to neutral
        TCA0.SINGLE.CMP2BUF = SERVO_PWM_DUTY_NEUTRAL;
    }
}