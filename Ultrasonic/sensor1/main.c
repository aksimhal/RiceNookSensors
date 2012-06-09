//******************************************************************************
//                MSP430G22x1
//             -----------------
//            |                 |
//        >---|P1.1/A1      P1.0|-->LED
//
//******************************************************************************
#include "msp430G2553.h"

unsigned int measure;
unsigned int measure_1;
unsigned int measure_2;
char up=0;

main()
{

	WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT

	//***Configure clock
	// we need DCO@1MHZ -> SMCLCK -> TA
	BCSCTL1 |= CALBC1_1MHZ;         //
	DCOCTL |= CALDCO_1MHZ;          // dco at 1mhz
	BCSCTL2 &= ~SELS;               // select dco for smclck source
	BCSCTL2 |= DIVS0;               // select no division

	//***TimerA capture configuration

	//rising edge + synchronous + p1.1 + capture + capture/compare interrupt enable
    TACCTL0 |= CM_1 + SCS + CCIS_0 + CAP + CCIE;
	//select smclock for timer a source + make taccr0 count continously up + no division
    TACTL |= TASSEL_2 + MC_2 + ID_0;

  	//***Enable interrupts
  	_BIS_SR(GIE);   // general interrupt enable

    //***Pins config
	P1DIR = BIT0;   // P1.0 output
	P1SEL = BIT1;
	P1OUT=0;        // turn led off
	
	//***Loop
	while (1)
	{ }
}

//***timerA interrupt routine
#pragma vector=TIMER0_A0_VECTOR
__interrupt void TimerA0(void)
{
		/*timerA was configured to CM_1(rising edge)
		 * so let's check if this is the first time the routine is called
		 * we check this by ensuring we are not capturing falling edges (CM_2)
		 */
		if(!(TACCTL0 & CM_2)) //rising edge (first time)
		{
			measure_1=TACCR0;
			TACCTL0 |= CM_3; //after the first time we want to catch both edges (CM_3)
		}
		else  // this is not the first time
		{
			if(up) //is this the rising edge?
			{
				measure_1=TACCR0;  // take first time measure
			}
			else //is this the falling edge?
			{
				measure_2=TACCR0; //take second time measure
				measure=(measure_2-measure_1)/58; // microseconds / 58 = centimeters
				if(measure>30) //is the distance more than 30cm?
				{
					P1OUT = 1; // turn led on
				}
				else
				{
					P1OUT=0;  //turn led off
				}
			}
			up=!up; //if this was the rising edge, the next one will be a falling edge, and vice-versa
		}
		TACTL &= ~TAIFG; //clear timer A interrupt flag, so the chip knows we handled the interrupt
}
