/* 
 * File:   main.c
 * Author: Kari-Pekka Turtiainen / kpturt@utu.fi
 *
 * Created on 14 November 2021, 01:10
 * Target device: ATmega4809 Curiosity Nano
 * 
 * This program does the following: When powered up the device starts counting
 * down from 9 to 0. If the timer reaches zero the device "explodes", meaning
 * that the display starts blinking the value 0.
 * If the red wire is "cut" (removed) before the timer reaches zero,
 * the countdown stops and the program becomes halted.
 */

#include <avr/io.h> 
#include <avr/interrupt.h> // For interrupts and sei() + cli()
#include <avr/cpufunc.h> // To enable CCP register change
#include <avr/sleep.h> // For superloop idle

// Global variable (volatile!), 1 = TRUE and running, 0 = FALSE and halted
volatile uint8_t g_running = 1;
// Global variable for counting ticks
volatile uint8_t g_clockticks = 0;

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

/* 
 * This function is copied and modified from technical brief TB3213  
 * To enable writing to CCP and enable PIT
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
     // Enable Periodic Interrupt 
     RTC.PITINTCTRL = RTC_PI_bm; 
     // Set period to 4 096 cycles (1/8 second) and enable PIT function 
     RTC.PITCTRLA = RTC_PERIOD_CYC4096_gc | RTC_PITEN_bm;
}
 
int main(void) 
{
    rtc_init(); // Initialise RTC timer's PIT interrupt function
    
    PORTA.DIRCLR = PIN4_bm; // Sets PORTA (stopper/red wire) pin 4 as input (0)
    PORTF.DIRSET = PIN5_bm; // Set on-board led as output
    PORTF.OUTSET = PIN5_bm;
    PORTC.DIRSET = 0xFF; // Sets PORTC (LED display) ports as outputs (1)

    /*If the wire in PORTA pin 4 loses connection to the ground,
     *internal pull-up resistor wins and PA4 input becomes HIGH and
     *triggers an interrupt due to a rising edge. 
     *PULLUPEN = enable bit mask, RISING = rising edge*/
    PORTA.PIN4CTRL = PORT_PULLUPEN_bm | PORT_ISC_RISING_gc;
    
    //set_sleep_mode(SLPCTRL_SMODE_IDLE_gc); // Set IDLE sleep mode, not needed?
    sei(); // Enables interrupts
    
    uint8_t index = 10; // Display starts from number 9
    
    // Main superloop
    while(1)
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
        
        // If program is halted disable interrupts
        if(g_running == 0)
        {
            cli(); 
        }
        
        // If one second has passed do something
        if(g_clockticks < 9)
        {
            index = 9 - g_clockticks;
        } else
        {
            index = 0;
        }
        
        /*When timer reaches below index 1 (zero)
         *blink the screen between zero and empty. */
        
        if(index == 0)
        {
            PORTF.OUTTGL = PIN5_bm; // Toggle on-board LED (PF5)
            index += 1; // Add one to index for blinking
        }
        else if(index < 2)
        {
            PORTF.OUTTGL = PIN5_bm; // Toggle on-board LED (PF5)
        }     
        
        // Changes display to a number marked by index of array
        PORTC.OUT = seven_segment_numbers[index];
        // Toggle device into sleep mode until next interrupt
        sleep_mode();
    }
}

ISR(PORTA_PORT_vect)
{
    // Clears interrupt flag(s) by writing 1 over the module
    PORTA.INTFLAGS = 0xFF;
    /* When an interrupt happens halt the main superloop via global variable
     * but only if the timer hasn't reached 0.
     */
    if(g_clockticks < 9)
    {
        g_running = 0;
    }
}

ISR(RTC_PIT_vect)
{
    // Clears interrupt flag(s) by writing 1 over the module
    RTC.PITINTFLAGS = 0xFF;
    
    // Counter to count seconds
    static uint8_t counter = 0;
    counter += 1;
    
    // When 1 second has passed, add to the global tick variable and reset count
    if(counter == 8)
    {
        g_clockticks += 1;
        counter = 0;
    }
}

