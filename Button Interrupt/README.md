# Button Interrupt
The objective for this portion of the lab was to recreate the Button Blink functionality using interrupts instead of polling as it is a more efficient way of checking for a state change. Rather than polling for changes at all times, interrupts allow for the same functionality without having to check at all times. Instead, whenever there is a change, such as with the button press in this case, the desired output will occur using the interrupt.

# Interrupt Code for the MSP430G2553
The code starts by disabling the built-in watchdog timer, as we want our code to run infinitely. The next step is to set the port directions and specify the functionality. P1.0 is set to the output direction, as this pin controls the green LED on the board. The button is then configured by enabling the internal resistor and setting it to pull-up. This provides the button functionality that is desired. The interrupt was then set to be triggered by pin 1.3 (the button) and the interrupt flag was cleared in order to allow for the code to enter the interrupt service routine. The service routine was set so that when the button was pressed, an interrupt would occur which would toggle the LED and turn it on. After the LED lights up, it remains on until another interrupt is detected, which turns the LED off.

# Interrupt Code for the MSP430F5529
The code for the F5529 is extremely similar to the G2553. The only notable difference is the pins are slightly different due to the board setup. Other than that, the functionality of the code is exactly the same and it operate in the same manner.


