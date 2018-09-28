/*Author: Nick Scamardi
 *Written: September 25, 2018
 *Last Updated: September 25, 2018
 */

#include <msp430.h>
void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // Disable the watch dog timer
    PM5CTL0 &= ~LOCKLPM5;   //Disable the default high-impedance mode


    P1DIR |= BIT0;  // Set P1.0 to output
    P2DIR |= BIT0;  // Set P2.0 to output

    TB0CTL = TBSSEL_1 + MC_1 + ID_3;    // TimerB0 Control: ACLK, Up Mode, Internal Divider (Divide ACLK by 8)
    TB0CCTL0 = CCIE;    // Capture Compare Interrupt Enabled
    TB0CCR0= 1000;  // Set Capture Compare Register (Controls Blink Rate for Red LED)

    TB1CTL = TBSSEL_1 + MC_1 + ID_3;    // TimerB1 Control: ACLK, Up Mode, Internal Divider (Divide ACLK by 8)
    TB1CCTL0 = CCIE;    // Capture Compare Interrupt Enabled (Controls Blink Rate for Green
    TB1CCR0 = 5000; // Set Capture Compare Register (Controls Blink Rate for Green LED)

    __enable_interrupt();   // Enables interrupt algorithm

    for(;;);    // Infinite for loop
}

// Interrupt service routine for Timer B instance 0
#pragma vector = TIMER0_B0_VECTOR
__interrupt void TB0_ISR(void)
{
    P1OUT ^= BIT0;      // Toggle P1.0 (Red LED)
}

// Interrupt service routine for Timer B instance 1
#pragma vector = TIMER1_B0_VECTOR
__interrupt void TB1_ISR(void)
{
    P2OUT ^= BIT0;      // Toggle P2.0 (Green LED)
}
