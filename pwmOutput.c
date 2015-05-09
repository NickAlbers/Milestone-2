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
void Set_PWM(unsigned long pwm_freq, float duty)
{
    unsigned long clocks_per_period = SysCtlClockGet () / pwm_freq;
    unsigned long clocks_per_pulse = clocks_per_period * (duty/100);

    PWMGenPeriodSet (PWM_BASE, PWM_GEN_2, clocks_per_period);
    PWMPulseWidthSet (PWM_BASE, PWM_OUT_4, clocks_per_pulse);

}

