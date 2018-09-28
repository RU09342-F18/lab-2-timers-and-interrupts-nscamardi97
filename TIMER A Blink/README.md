# TIMER A Blink
The objective for this part of the lab was to use Timer A to control the blink rate of two LEDs. This is almost identical to the functionality of the multiple blink, except a timer is used to control the blink rate rather than if statements. This exercise was designed to interface with the Timer A peripheral and gain a better understanding of how to configure it.

# Code for the MSP430G2553
The first step is to disable the built-in watchdog timer. There is a line of code that had to be included in order to allow Timer A to function correctly on the G2553 if using ACLK. This line can be seen below:

BCSCTL3 = LFXT1S_2;
 
The line of code forces ACLK to ignore the external crystal on the board and to use the internal oscillator instead. This is required for proper functionality. The LED pins are then set to the output direction using the P1DIR macro, with P1.0 being set ON initially and P1.6 being set to off initially. This was an arbitrary design feature that was included so that the LEDs would be out of sync.
 
Next, Timer A0 had to be configured using TACTL. This allows the user to control different aspects of the timer, such as the clock being used, which mode to set the timer to, etc. For my code, the design choice I implemented was to use ACLK, due to its slower frequency. The timer was also set to up mode and the clock was divided by a factor of 4. All of this is accomplished with the following line:
 
TA0CTL = TASSEL_1 + MC_1 + ID_2;
 
The same steps were repeated to configure Timer A1 and all of the configurations remain constant. The capture compare registers also had to be set up correctly. First, capture compare interrupt was enabled for both Timer A0 and Timer A1. A value was then placed into those registers in order to control the blink rate of the two LEDs. Once everything was initialized, the interrupt is enabled and the LEDs are toggled based on the rate set in the capture compare registers.
 
# Code for the MSP430FR2311
The FR2311 code is again extremely similar to that of the G2553. However, this board does not have Timer A so the Timer B peripheral was used instead. Configuration was pretty much the same, with the exception of a few pin changes due to the different board. For all intents and purposes, Timer B served the same function as Timer A did for the G2553. Both libraries require the msp430.h library.
