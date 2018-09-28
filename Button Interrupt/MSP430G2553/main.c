/*Author: Nick Scamardi
 *Written: September 24, 2018
 *Last Updated: September 24, 2018
 */

#include <msp430.h>

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// Disable watchdog timer
    P1DIR = BIT0;   // Set P1.0 as output
    P1REN = BIT3;   // Enable internal resistor
    P1OUT = BIT3;   // Connects internal resistor to power (making it a pull-up)

    P1IE = BIT3;    // Set P1.3 as interrupt pin (interrupts are triggered w/ changes to this pin)
    P1IFG &= ~BIT3;

    __enable_interrupt();   // Enables interrupt algorithm

    for(;;){};  // Infinite for loop (code continues to execute)
}

// Interrupt service routine for P1
#pragma vector = PORT1_VECTOR
__interrupt void Port_1(void)
{
    P1OUT ^= (BIT0);    // Toggles P1.0
    P1IFG = ~BIT3;      // Reset interrupt flag for P1.3
}
