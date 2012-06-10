// LaunchPad PIR Sensor test
// Interfaces a Parallax PIR sensor with the LaunchPad
// When the PIR senses movement, LED1 will be on for ~2s, then off
// LED2 is always on
// written by suspended-chord/gatesphere (http://suspended-chord.info/)
// released into the public domain

// circuit:
// PIR sensor -
//    OUT ->  P1.5
//    +   ->  TP1 (5V)
//    -   ->  TP3 (GND)
// PIR sensor jumper set to L

#include <msp430g2553.h>
unsigned int i = 0;
int j = 0;
unsigned int tx[] = {0x4d, 0x6f, 0x76, 0x65, 0x6d, 0x65, 0x6e, 0x74, 0x20};

void main() {
  WDTCTL = WDTPW + WDTHOLD; // kill wdt

  //Set up UART
  BCSCTL1 = CALBC1_1MHZ;                    // Set DCO
  DCOCTL = CALDCO_1MHZ;
  P1SEL = BIT1 + BIT2 ;                     // P1.1 = RXD, P1.2=TXD
  P1SEL2 = BIT1 + BIT2 ;                     // P1.1 = RXD, P1.2=TXD
  UCA0CTL1 |= UCSSEL_2;                     // SMCLK
  UCA0BR0 = 104;                            // 1MHz 9600
  UCA0BR1 = 0;                              // 1MHz 9600
  UCA0MCTL = UCBRS0;                        // Modulation UCBRSx = 1
  UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**

  //Set up LED
  P1DIR = BIT0 + BIT6; // set LED1 and LED2 to OUT
  P1OUT = ~(BIT0 + BIT6); // LED2 always on - indicates power
  P1IES &= ~BIT5; // low-high edge initially
  P1IFG &= ~BIT5; // prevent immediate interrupt
  P1IE |= BIT5; // enable interrupts on P1.5
  _BIS_SR(LPM4_bits + GIE); // enable GPIO interrupts and send into LPM4

  //for (;;); // loop forever
}

// interrupt for P1
#pragma vector = PORT1_VECTOR
__interrupt void P1_ISR() {
  if ((P1IFG & BIT5) == BIT5) { // if motion sensed
	IE2 |= UCA0TXIE;                          // Enable USCI_A0 RX interrupt
	i++;
	P1IFG &= ~BIT5; // clear interrupt flag
    P1OUT ^= BIT0; // toggle LED1
    P1IES ^= BIT5; // toggle edge
  } else {
	i++;
	P1IFG = 0; // clear all other flags to prevent infinite interrupt loops
  }
}

#pragma vector=USCIAB0TX_VECTOR
__interrupt void USCI0TX_ISR(void)
{

	for (j=0;j<9;j++)
	{
		UCA0TXBUF = tx[j];
		P1OUT ^= BIT6; // toggle LED2
		__delay_cycles (100000);
		//P1OUT ^= BIT6; // toggle LED2
	}
	j = 0;
	IE2 &= ~UCA0TXIE;                       // Disable USCI_A0 TX interrupt
}
