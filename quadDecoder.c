//*****************************************************************************
//
// quadEncoder.c - Program to monitor a quadrature encoder and report
//
// Author:  P.J. Bones	UCECE
// Last modified:	17.3.2015
//*****************************************************************************

#include "quadDecoder.h"

//*****************************************************************************
// Initialise Quadrature Decoder
//*****************************************************************************

void Init_Quad_Decoder (void)
{
	//Initialise the decoding interrupt on port F
    SysCtlPeripheralEnable (SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_5 | GPIO_PIN_7);

    // Enable the pin change interrupt
    GPIOPinIntEnable (GPIO_PORTF_BASE, GPIO_PIN_5 | GPIO_PIN_7);

    // Register the handler for Port F into the vector table
    GPIOPortIntRegister (GPIO_PORTF_BASE, Quad_Decoder_ISR);

    //Configure pins 27 and 29, interrupt handler needs to run whenever a
    //pin changes state
    GPIOPadConfigSet (GPIO_PORTF_BASE, GPIO_PIN_5 | GPIO_PIN_7,
    				  GPIO_STRENGTH_8MA, GPIO_PIN_TYPE_STD);

    // Set up the pin change interrupt (both edges)
    GPIOIntTypeSet (GPIO_PORTF_BASE, GPIO_PIN_5, GPIO_BOTH_EDGES);

    //Enable interrupts on Port F
    IntEnable (INT_GPIOF);	// Note: INT_GPIOF defined in inc/hw_ints.h

}


//*****************************************************************************
//The Interrupt handler for the quadrature encoder (Pins 27 and 29)
//*****************************************************************************

void Quad_Decoder_ISR ()
{
	//Initialise a variable to hold the current and previous pin states as a
	//set of bits.
	static int8_t channelVals = 0;

	//Clear the interrupt flag
	GPIOPinIntClear (GPIO_PORTF_BASE, GPIO_PIN_5 | GPIO_PIN_7);

	//Read the pins PORTF is 8 bits long, so bit shift them to positions
	//2 and 3 (oif 4 bit binary) respectively for compatibility,
	// then OR Pin 5 and Pin 7 together to get a single 4 bit representation.
	// e.g 0x1100
	int8_t AB = (GPIOPinRead (GPIO_PORTF_BASE, GPIO_PIN_5) >> 5) |
				(GPIOPinRead (GPIO_PORTF_BASE, GPIO_PIN_7) >> 6) ;

	// Initialise a lookup table, moving along the table shows possible changes
	// from state to state, since each state can only change to two others,
	// left or right
	static const int8_t lookup_table[] = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0};

	//Remember previous state, and then add the current state to the state list
	channelVals <<= 2;
	channelVals |= (AB);

	//Update Yaw value by checking the lookup table.
	yawAngle += lookup_table[channelVals & 0x0F];


}

//*****************************************************************************
// Gets the yaw value and converts it to degrees
//*****************************************************************************

int16_t Get_Yaw()
{
	return (yawAngle * ENCODERSCALER);
}

