// LaunchPad PIR Sensor
// Interfaces 2 Parallax PIR sensors with the LaunchPad
// When the PIR1 (on P1.5) senses movement, LED1 will be on for ~2s, then off
// When the PIR2 (on P2.0) senses movement, LED2 will be on for ~2s, then off
// written by suspended-chord/gatesphere (http://suspended-chord.info/), modified by Vinay Dandekar and Shiv Sinha
// initial version in the public domain, current version is not (but on GitHub)

// circuit:
// PIR sensor 1 -
//    OUT ->  P1.5
//    +   ->  VCC (3.3V)
//    -   ->  GND
// PIR sensor 2 -
//    OUT ->  P2.0
//    +   ->  VCC (3.3V)
//    -   ->  GND
// PIR sensor jumper set to L

#include <msp430g2553.h>

unsigned int In=0, Out=0, One=0, Two=0; // Flag variables


void main() {
	WDTCTL = WDTPW + WDTHOLD; // kill wdt

	// Set up UART
	BCSCTL1 = CALBC1_1MHZ; // Set DCO
	DCOCTL = CALDCO_1MHZ;
	P1SEL = BIT1 + BIT2; // P1.1 = RXD, P1.2=TXD
	P1SEL2 = BIT1 + BIT2; // P1.1 = RXD, P1.2=TXD
	UCA0CTL1 |= UCSSEL_2; // SMCLK
	UCA0BR0 = 104; // 1MHz 9600
	UCA0BR1 = 0; // 1MHz 9600
	UCA0MCTL = UCBRS0; // Modulation UCBRSx = 1
	UCA0CTL1 &= ~UCSWRST; // **Initialize USCI state machine**
	IE2 |= UCA0RXIE;                          // Enable USCI_A0 RX interrupt

	// Set up LEDs
	P1DIR = BIT0 + BIT6; // set LED1 and LED2 to OUT
	P1OUT &= ~(BIT0 + BIT6); // Turn LEDs off

	// Set up input
	P1IES &= ~BIT5; // low-high edge initially
	P1IFG &= ~BIT5; // prevent immediate interrupt
	P1IE |= BIT5; // enable interrupts on P1.5

	P2IES &= ~BIT0; // low-high edge initially
	P2IFG &= ~BIT0; // prevent immediate interrupt
	P2IE |= BIT0; // enable interrupts on P2.0

	__delay_cycles(40000000);	//5 seconds
	P1OUT ^= BIT0 + BIT6;
	__delay_cycles(40000);	//40 ms
	P1OUT ^= BIT0 + BIT6;
	__delay_cycles(40000);
	P1OUT ^= BIT0 + BIT6;
	__delay_cycles(40000);
	P1OUT ^= BIT0 + BIT6;
	__delay_cycles(40000);
	P1OUT ^= BIT0 + BIT6;
	__delay_cycles(40000);
	P1OUT ^= BIT0 + BIT6;


	_BIS_SR(LPM4_bits + GIE); // enable GPIO interrupts and send into LPM4


}

// interrupt for P1
#pragma vector = PORT1_VECTOR
__interrupt void P1_ISR() {
	if ((P1IN & BIT5) == BIT5) { // if motion sensed on PIR 1.5
		if (Two) { //this means someone is walking out
			Out = 1;
			IE2 |= UCA0TXIE; // Enable USCI_A0 TX interrupt
		} else { //this means that PIR 1.5 is triggered first
			One = 1;
		}

		//i++;
		P1IFG &= ~BIT5; // clear interrupt flag
		P1OUT ^= BIT0; // toggle LED1

	} else {
		//i++;
		P1IFG = 0; // clear all other flags to prevent infinite interrupt loops
	}
}

// interrupt for P2
#pragma vector = PORT2_VECTOR
__interrupt void P2_ISR() {
	if ((P2IN & BIT0) == BIT0) { // if motion sensed on PIR 2.0
		if (One) { //this means someone is walking in
			In = 1;
			IE2 |= UCA0TXIE; // Enable USCI_A0 TX interrupt
		} else {
			Two = 1; //PIR 2.0 triggered first
		}


		P2IFG &= ~BIT0; // clear interrupt flag
		P1OUT ^= BIT6; // toggle LED2

	} else {

		P2IFG = 0; // clear all other flags to prevent infinite interrupt loops
	}

}

#pragma vector=USCIAB0TX_VECTOR
__interrupt void USCI0TX_ISR(void) {
	if(In){
		UCA0TXBUF = 'I';
	}
	else if (Out){
		UCA0TXBUF = 'O';
	}

	Two = 0;
	One = 0;
	In = 0;
	Out = 0;

	IE2 &= ~UCA0TXIE; // Disable USCI_A0 TX interrupt
}

//Reset Vector
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void) {



	if (UCA0RXBUF == 'R'){ //if R is received, reset

		  P1OUT ^= BIT0 + BIT6; //toggle LED
		  Two = 0;
		  One = 0;
		  In = 0;
		  Out = 0;
	}

	//IE2 &= ~UCA0RXIE; // Disable USCI_A0 TX interrupt
}
