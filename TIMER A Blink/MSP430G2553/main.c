/*Author: Nick Scamardi
 *Written: September 25, 2018
 *Last Updated: September 25, 2018
*/

#include <msp430.h>
void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // Disable the watch dog timer
    BCSCTL3 = LFXT1S_2;         // Makes ACLK ignore external crystal & use internal oscillator

    P1OUT |= BIT0;              // Set P1.0 to ON initially
    P1OUT &= ~BIT6;             // Set P1.6 to OFF initially
    P1DIR |= (BIT0 + BIT6);     // Set P1.0 (Green LED) & P1.6 (Red LED) as outputs

    TA0CTL = TASSEL_1 + MC_1 + ID_2;    // Control for TimerA0: ACLK, Up mode, Internal Divider (Divide clk by 4)
    TA0CCTL0 = CCIE;    // Capture Compare Interrupt Enabled
    TA0CCR0= 1000;      // Set Capture Compare Register

    TA1CTL = TASSEL_1 + MC_1 + ID_2;    // Control for TimerA1: ACLK, Up mode, Internal Divider (Divide clk by 4)
    TA1CCTL0 = CCIE;    // Capture Compare Interrupt Enabled
    TA1CCR0 = 3000;     // Set Capture Compare Register

    __enable_interrupt();   // Enables interrupt algorithm

    for(;;);    // Infinite for loop
}

// Interrupt service routine for Timer B instance 0
#pragma vector = TIMER0_A0_VECTOR
__interrupt void TIMER_A0(void)
{
    P1OUT ^= BIT0;      // Toggle P1.0 (Red LED)
}

// Interrupt service routine for Timber B instance 1
#pragma vector = TIMER1_A0_VECTOR
__interrupt void TIMER_A1(void)
{
    P1OUT ^= BIT6;      // Toggle P1.6 (Green LED)
}
