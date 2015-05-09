//*****************************************************************************
// main.c
//
// Created on: May 8, 2015
// Author: Nick
//*****************************************************************************

//Include drivers
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "driverlib/adc.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "driverlib/interrupt.h"
#include "driverlib/debug.h"
#include "drivers/rit128x96x4.h"
#include "inc/lm3s1968.h"


//Include standard C library files
#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"

//Include program modules
#include "altitudeMonitor.h"
#include "pwmOutput.h"
#include "quadDecoder.h"
#include "circBuf.h"

//Declare global strings
char yawStr[] = "Yaw";
char altStr[] = "Alt";

//Globals
static uint16_t ul_AltitudeVal;
circBuf_t g_AltitudeBuff;		    // Buffer of size BUF_SIZE integers (sample values)
unsigned long gul_AltitudeSampCnt;	// Counter for the interrupts

//Function Prototypes
void Init_Clock (void);
void Init_Display (void);
void Init_Ref_Pin (void);
void Display_Val (volatile int16_t value, char* metric, int y_Pos);

//*****************************************************************************
// Initialise system clock
//*****************************************************************************
void Init_Clock (void)
{

	// Set the clock rate. From Section 19.1 in stellaris_peripheral_lib_UG.doc:
	//  "In order to use the ADC, the PLL must be used; the PLL output will be
	//  used to create the clock required by the ADC." ADC rate = 8 MHz / 10.
	SysCtlClockSet(SYSCTL_SYSDIV_10 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN |
                   SYSCTL_XTAL_8MHZ);

	// Set up the period for the SysTick timer.  The SysTick timer period is
	// set as a function of the system clock.
	SysTickPeriodSet(SysCtlClockGet() / SAMPLE_RATE_HZ);
	//
	// Register the interrupt handler
    SysTickIntRegister(Sys_Tick_ISR);
	//
	// Enable interrupt and device
	SysTickIntEnable();
    SysTickEnable();
}

//*****************************************************************************
// Initialise OLED display
//*****************************************************************************
void Init_Display (void)
{
	RIT128x96x4Init(1000000);
}

//*****************************************************************************
// Generic display function, takes an integer value, a metric, and the
// y position to disable the string at
//*****************************************************************************
void Display_Val (volatile int16_t value, char* metric, int y_Pos)
{
	// Generate a string with the current passed value and display on the OLED
	// at the desired positon (X, Y, Level)

	char string [30];
	sprintf (string, "%s: %d  ", metric, value);
	RIT128x96x4StringDraw (string, 5, y_Pos, 15);
}

//************************************************************
// Initialisation function to provide a Vcc source on Pin 56
//************************************************************
void Init_Ref_Pin (void)
{
   // To set Pin 56 (PD0) as a +Vcc low current capacity source:
   SysCtlPeripheralEnable (SYSCTL_PERIPH_GPIOD);
   GPIOPinTypeGPIOOutput (GPIO_PORTD_BASE, GPIO_PIN_0);
   GPIOPadConfigSet (GPIO_PORTD_BASE, GPIO_PIN_0, GPIO_STRENGTH_8MA,
      GPIO_PIN_TYPE_STD_WPU);
   GPIOPinWrite (GPIO_PORTD_BASE, GPIO_PIN_0, GPIO_PIN_0);
}

//*****************************************************************************
// Function to display the mean ADC value (10-bit value, note) and sample count
//*****************************************************************************
//void displayMeanVal(int meanVal, int count)
//{
//	char string[100];
//
//    RIT128x96x4StringDraw("ADC0 (Pin 62)", 5, 24, 15);
//    RIT128x96x4StringDraw("sampled at 10 Hz", 5, 34, 15);
//	sprintf(string, "Mean value = %d %", meanVal & 0X03FF);
//    RIT128x96x4StringDraw(string, 5, 44, 15);
//	sprintf(string, "Count = %d %", count & 0X0FFF);
//    RIT128x96x4StringDraw(string, 5, 54, 15);
//}


//*****************************************************************************
// Main Function
//*****************************************************************************
int main (void)
{
	Init_Quad_Decoder();
	Init_Display();
	Init_PWM();
	Init_ADC();
	Init_Clock();
	Init_Ref_Pin ();
	initCircBuf (&g_AltitudeBuff, BUF_SIZE);

    // Set the period and pulse width of PWM
    Set_PWM(DEFAULT_RATE_HZ, DEFAULT_DUTY);

	//uint64_t ul_ADC0Value = 0;
    int sum;
    int i;

	//Enable processor interrupts.
	IntMasterEnable ();

	while (1) // While both pins are high
	{
		sum = 0;

		for (i = 0; i < BUF_SIZE; i++)
		{
			sum = sum + readCircBuf (&g_AltitudeBuff);
		}

		Display_Val (Get_Yaw(),yawStr, 5);
		Display_Val ((sum / BUF_SIZE),altStr, 15);
		//displayMeanVal(sum / BUF_SIZE, (int) gul_AltitudeSampCnt);

		// Cann comment this out for faster screen updating but with a
		// side effect of altitude changing rapidly
 		SysCtlDelay(SysCtlClockGet() / 24);
	}
}


