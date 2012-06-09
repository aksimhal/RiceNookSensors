/*
 * main.c
 *Turn the green led on every time the button is pressed
 * June 4 2012
 */

#include <msp430.h>

#define     BUTTON                BIT3
#define     BUTTON_OUT            P1OUT
#define     BUTTON_DIR            P1DIR
#define     BUTTON_IN             P1IN
#define     BUTTON_IE             P1IE
#define     BUTTON_IES            P1IES
#define     BUTTON_IFG            P1IFG
#define     BUTTON_REN            P1REN

void InitializeButton(void);
void main(void) {
	
	InitializeButton();
	WDTCTL = WDTPW + WDTHOLD;  //stop the watchdog timer
	P1DIR |= 0x41 ;  // 0x40 P1.6 output (green LED)
					// 0x01 P1.0 output (red LED)
					// 0x41 = 0x01+0x40 Displays both green & red LEDs

	while(1)
	{
		if ((BUTTON & P1IN))
			{
			P1OUT &= ~0x41;  //&= is AND
							// ~ is NOT
			}
		else
		{
			P1OUT |= 0x41; // |= is OR
		}
	}



}


void InitializeButton(void)                 // Configure Push Button
{
  BUTTON_DIR &= ~BUTTON;				// Direction
  BUTTON_OUT |= BUTTON;					// Output
  BUTTON_REN |= BUTTON;					// Resistor Enable
  BUTTON_IES |= BUTTON;					// Interrupt Edge Select
  BUTTON_IFG &= ~BUTTON;				// Interrupt Flag
  BUTTON_IE |= BUTTON;					// Interrupt Enable
}
