//*****************************************************************************
// main.c
//
// Created on: May 8, 2015
// Author: Nick
//*****************************************************************************
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "inc/lm3s1968.h"
#include "driverlib/adc.h"
#include "driverlib/pwm.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "driverlib/interrupt.h"
#include "driverlib/debug.h"
#include "drivers/rit128x96x4.h"

//Include standard C library files
#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"

//Include program modules
#include "altitudeMonitor.h"
#include "pwmOutput.h"
#include "quadDecoder.h"
#include "circBuf.h"
#include "display.h"

//Include configurations settings
#include "config.h"

//Function Prototypes
void Init_Clock (void);
void Init_Ref_Pin (void);

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
	SysTickPeriodSet(SysCtlClockGet() / ADC_SAMPLE_RATE_HZ);

	// Register the interrupt handler and enable interrupts and the device
    SysTickIntRegister(SysTickIntHandler);
	SysTickIntEnable();
    SysTickEnable();
}

//*****************************************************************************
// Initialisation function to provide a Vcc source on Pin 56
//*****************************************************************************
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
// Generates a map to convert the voltage inputs from the ADC values to
// percentage
//*****************************************************************************

int16_t Map_ADC(int16_t input, int16_t in_min, int16_t in_max, int16_t out_min,
				int16_t out_max)
{
  return (input - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

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
	Set_PWM(PWM_FREQ_HZ, PWM_DEFAULT_DUTY);

	int16_t PWM_Duty;
    int16_t sum;
    int16_t avgAltVolts;
    int16_t avgAltitude;
    int16_t altitudePercentage;
    unsigned int i;

	//Enable processor interrupts.
	IntMasterEnable ();
	while (1) // While both pins are high
	{
		sum = 0;
		for (i = 0; i < BUF_SIZE; i++)
		{
			sum = sum + readCircBuf (&g_AltitudeBuff);
		}

		// Convert ADC read to volts, and average across BUF_SIZE counts
		avgAltitude = sum/BUF_SIZE;
		avgAltVolts = Map_ADC(avgAltitude,  MIN_ALT_ADC, MAX_ALT_ADC,
											MIN_ALT_VOLTS, MAX_ALT_VOLTS);
		// Convert ADC voltage to a percentage
		// NOTE WELL: MAX ALT VOLTS and MIN ALT VOLTS are flipped since the ADC
		// output is inversely proportional to distance
		altitudePercentage = Map_ADC(avgAltVolts, MAX_ALT_VOLTS, MIN_ALT_VOLTS,
									MIN_ALT_PERCENT, MAX_ALT_PERCENT);

		// Set the duty cycle of the PWM relative to the altitude, with
		// max = 95% and min 5%
		PWM_Duty = Calc_PWM_Duty(avgAltitude);
		Set_PWM(PWM_FREQ_HZ, PWM_Duty);

		Display_Val (Get_Yaw(), "Yaw", 5);
		Display_Val ((avgAltVolts), "Altitude", 15);
		Display_Val ((altitudePercentage), "Altitude %", 25);
		Display_Val (gul_AltitudeSampCnt, "Count", 35);
		Display_Val (PWM_FREQ_HZ, "PWM Freq", 45);
		Display_Val (PWM_Duty, "PWM Duty", 55);
	}
}

