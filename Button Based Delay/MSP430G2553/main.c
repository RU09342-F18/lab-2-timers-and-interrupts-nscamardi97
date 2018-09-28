/*Author: Nick Scamardi
 *Written: September 26, 2018
 *Last Updated: September 26, 2018
 */

#include <msp430.h>

volatile unsigned int TC1 = 0;  // Timer Counter 1 initialized to 0 (Counter for P1.0)

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;   // Disable the watchdog timer
	BCSCTL3 = LFXT1S_2;         // Makes ACLK use internal oscillator

	P1DIR |= BIT6;  // Set P1.6 (Red LED) to output
    P1REN |= BIT3;   // Enable internal resistor
    P1OUT |= BIT3;   // Connects internal resistor to power (making it a pull-up)

    P1IE |= BIT3;    // Set P1.3 as interrupt pin (interrupts are triggered w/ changes to this pin)
    P1IES |= BIT3;   // Set P1.3 to interrupt on falling edge (high to low transition)

    TACCTL0 = CCIE; // Capture Compare Interrupt Enabled
    TACCR0 = 300;   // Set Capture Compare Register
    TACTL = TASSEL_1 + MC_1; // Timer A Control: ACLK, Up Mode


    __enable_interrupt();   // Enables interrupt algorithm
    for(;;){};  // Infinite for loop
}

// Interrupt service routine for TimerA0
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A(void)
{
    P1OUT ^= BIT6;  // Toggle P1.6 (Red LED ON)
}

// Interrupt service routine for Port 1
#pragma vector = PORT1_VECTOR
__interrupt void Port_1(void)
{
    if(P1IES & BIT3){   // Port 1 Interrupt Edge Select (Falling Edge)

        TACTL = TACLR;  // Clear Timer Settings
        TACTL = TASSEL_1 + MC_2 + ID_3; // Timer A Control: ACLK, Continuous mode, Internal Divider (Divide ACLK by 8)
        P1IES &= ~BIT3; // Set Interrupt Edge Select (Rising Edge)
    }

    else{
        TACCR0 = TA0R;  // Sets Capture Compare register to TimerA0 value
        TACTL = TASSEL_1 + MC_1 +ID_3;  // Timer A Control: ACLK, Up mode, Internal Divider (Divide ACLK by 8)
        P1IES |= BIT3;  // Set Interrupt Edge Select (Falling Edge)
    }

    P1IFG &= ~BIT3;    // Resets interrupt flag for P1.3

}
