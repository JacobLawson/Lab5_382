
//-----------------------------------------------------------------
// Name:	Jacob Lawson
// File:	lab5.c
// Date:	Fall 2014
// Purpose:	Remote etch-a-sketch
//-----------------------------------------------------------------

#include <msp430g2553.h>
#include "start5.h"

int16	packetData[34];
int8	packetIndex = 0;

void main(void) {

	//This sets up the block position
	unsigned char x, y, c;

	IFG1=0; 					// clear interrupt flag1
	WDTCTL=WDTPW+WDTHOLD; 		// stop WD

	BCSCTL1 = CALBC1_8MHZ;		//set up clock
	DCOCTL = CALDCO_8MHZ;


	init();
	initNokia();
	initMSP430();
	clearDisplay();
	drawBlock(y,x,c);

	x = 6;
	y = 4;
	c=0xFF;

	initMSP430();




	while(1){										//		Determine value of IrPacket
		if(packetIndex == 34){						// if one full signal is recieved, then the loop will iterate
			_disable_interrupt();
			int32 IrPacket = 0;
			int32 setBit = 0xF0000000;

			char i;
			for(i = 2; i<34; i++){
				int16 current = packetData[i];		// This is the current element
				if(current/10 < 100){
					IrPacket &= ~setBit;
				} else {
					IrPacket |= setBit;
				}
					setBit >>= 1;
				}
			packetIndex++;							// This just makes sure that the loop is not entered into again.
			initNokia();

//		Handle the button presses

			if (IrPacket == ZERO) {					//This is the process in which we pick the "color" of the block
							if(c == 0xFF){
								c = 0;
							} else if (c == 0){
								c = 0xFF;
							}
						}

						if (IrPacket == VOL_UP) {			//These just check for button presses in a particular direction.
							if (y>=1) y=y-1;
						} else if (IrPacket == VOL_DW) {
							if (y<=6) y=y+1;
						} else if (IrPacket == ONE) {
							if (x>=1) x=x-1;
						} else if (IrPacket == TWO) {
							if (x<=10) x=x+1;
						}

			drawBlock(y, x, c);					//draws the block
			initMSP430();						//Now we look for another IR input.
		}
	}
}

// -----------------------------------------------------------------------
//
// The purpose of this code is to decode the IR packets. This configures the MSP 430
// to allow it to have interrupts on positive edges and as a result work off of a
// time/clock cycle. The P2.6 pin has an ISR which serves to switch the sensitivity
// of the interrupt and in effect measure the times of the high/low pulses coming
// from the decoder.
//
// -----------------------------------------------------------------------
void initMSP430() {

	//setup interrupt pin
	P2SEL  &= ~BIT6;						// Setup P2.6 as GPIO not XIN
	P2SEL2 &= ~BIT6;
	P2DIR &= ~BIT6;
	P2IFG &= ~BIT6;						// Clear all interrupt flags
	P2IE  |= BIT6;						// Enable PORT 2 interrupt

	HIGH_2_LOW;

	TA0CCR0 = 0xFFFF;					// create a roll-over
	TACTL &= ~TAIFG;					// clear flag before interrupts are enabled
	TACTL = ID_3 | TASSEL_2 | MC_1 | TAIE;		// Use 1:1 off MCLK. Enable interrupts

	_enable_interrupt();
}

// -----------------------------------------------------------------------
//
// We want an interrupt to happen whenever we get a positive or negative edge
// to account for whenever a pin changes.
//
// -----------------------------------------------------------------------

#pragma vector = PORT2_VECTOR			// This is from the MSP430G2553.h file
__interrupt void pinChange (void) {

	int8	pin;
	int16	pulseDuration;

	if (IR_PIN)
		pin=1;
	else
		pin=0;

//-------------------------------
//NEGATIVE EDGE
//-------------------------------

		if(pin == 0){
			pulseDuration = TAR;
			TACTL = 0;
			packetData[packetIndex++] = pulseDuration;
			LOW_2_HIGH; 				// Setup pin interrupt to go on negative edge
		}

//-------------------------------
//POSITIVE EDGE
//-------------------------------
		else{
			TAR = 0x0000;						// time starts at 0
			TA0CCR0 = 0xFF00;					// 16mS roll-over period
			TACTL &= ~TAIFG;
			TACTL = ID_3 | TASSEL_2 | MC_1 | TAIE;
			HIGH_2_LOW; 						// Setup pin interrupt to go on positive edge
		}


	P2IFG &= ~BIT6;			//Prevent process from starting again.

}

// -----------------------------------------------------------------------
//
// This interrupt is a way of reseting the reciever and packetIndex.
//
// -----------------------------------------------------------------------

#pragma vector = TIMER0_A1_VECTOR			// This is from the MSP430G2553.h file
__interrupt void timerOverflow (void) {

	packetIndex = 0;
	TACTL = 0;
	TACTL &= ~TAIFG;
	initMSP430();
}
