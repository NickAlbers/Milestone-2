//*****************************************************************************
// pwmOutput.c
//
// Created on: May 8, 2015
// Author: Nick
//*****************************************************************************

#include "pwmOutput.h"

//*****************************************************************************
// Initialise PWM
//*****************************************************************************

void Init_PWM ()
{
    SysCtlPeripheralEnable (SYSCTL_PERIPH_PWM);

    // Enable the peripheral used for the pwm channel
    SysCtlPeripheralEnable ( SYSCTL_PERIPH_GPIOF);

    // Set specified pin as PWM
    GPIOPinTypePWM (GPIO_PORTF_BASE, PWM4_PIN);
    PWMGenConfigure (PWM_BASE, PWM_GEN_2,
                     PWM_GEN_MODE_UP_DOWN | PWM_GEN_MODE_NO_SYNC);

    // Enable the PWM output signal and the PWM generator
    PWMOutputState (PWM_BASE, PWM_OUT_4_BIT, true);
    PWMGenEnable (PWM_BASE, PWM_GEN_2);

}

//*****************************************************************************
// Set the Duty Cycle of the specifed PWM
//*****************************************************************************
void Set_PWM(unsigned long ul_PWMFreq, float f_Duty)
{
    unsigned long ul_ClocksPerPeriod = SysCtlClockGet () / ul_PWMFreq;
    unsigned long ul_ClocksPerPulse = ul_ClocksPerPeriod* (f_Duty/100);

    PWMGenPeriodSet (PWM_BASE, PWM_GEN_2, ul_ClocksPerPeriod);
    PWMPulseWidthSet (PWM_BASE, PWM_OUT_4, ul_ClocksPerPulse);

}

//***********************************************************
// Calculates the Duty Cycle relative to the altitude
//***********************************************************

int16_t Calc_PWM_Duty(volatile int16_t altitude)
{
	// Scale the encoder value from the adc input in volts to a  value in percentage

	int16_t calcDuty;
	calcDuty = (100.00 - altitude);

	//Keep Duty within pre defined minimum and maximum bounds
	if (calcDuty > 95.00)
	{
		calcDuty = 95.00;
	}
	if (calcDuty < 5.00)
	{
		calcDuty = 5.00;
	}
	return calcDuty;
}

