/*Author: Nick Scamardi
 *Written: September 26, 2018
 *Last Updated: September 26, 2018
 */

#include <msp430.h>

volatile unsigned int TC1 = 0;  // Timer Counter 1 initialized to 0 (Counter for P1.0)

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // Disable the watchdog timer

    P1DIR |= BIT0;  // Set P1.0 (Red LED) to output
    P1REN |= BIT1;   // Enable internal resistor
    P1OUT |= BIT1;   // Connects internal resistor to power (making it a pull-up)

    P1IE |= BIT1;    // Set P1.1 as interrupt pin (interrupts are triggered w/ changes to this pin)
    P1IES |= BIT1;   // Set P1.1 to interrupt on falling edge (high to low transition)

    TA0CCTL0 = CCIE;    // Capture Compare Interrupt Enable
    TA0CCR0 = 100;  // Set Capture Compare Register
    TA0CTL = TASSEL_1 + MC_1 + ID_3;    // TimerA0 Control: ACLK, Up mode, Divide clock by 8


    __enable_interrupt();   // Enables interrupt algorithm

    for(;;){};  // Infinite for loop
}

// Interrupt service routine for Timer A
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer0_A0(void)
{
    P1OUT ^= BIT0;  // Toggle P1.0 (Red LED ON)
}

// Interrupt service routine for P1
#pragma vector = PORT1_VECTOR
__interrupt void Port_1(void)
{
    if(P1IES & BIT1){   // Port 1 Interrupt Edge Select (Falling Edge)

        TA0CTL = TACLR; // Clear timer settings
        TA0CTL = TASSEL_1 + MC_2 + ID_3;    // TimerA0 Control: ACLK, Continuous mode, Divide clock by 8
        P1IES &= ~BIT1; // Set Interrupt Edge Select (Rising Edge)
    }

    else{
        TA0CCR0 = TA0R; // Capture Compare Register gets value of TimerA0
        TA0CTL = TASSEL_1 + MC_1 +ID_3; // TimerA0 Control: ACLK, Up mode, Divide clock by 8
        P1IES |= BIT1;  // Set Interrupt Edge Select (Falling Edge)
    }

    P1IFG &= ~BIT1;    // Resets interrupt flag for P1.1

}
