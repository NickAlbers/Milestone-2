//*****************************************************************************
// pwmOutput.h
//
// Created on: May 8, 2015
// Author: Nick
//*****************************************************************************

#ifndef PWMOUTPUT_H_
#define PWMOUTPUT_H_

//Includes
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/lm3s1968.h"

#include "driverlib/sysctl.h"
#include "driverlib/pwm.h"
#include "driverlib/gpio.h"

#include "stdio.h"
#include "driverlib/pwm.h"

//Function Protypes
void Init_PWM ();
void Set_PWM(unsigned long pwm_freq, float duty);

//Constants
#define DEFAULT_RATE_HZ 150
#define DEFAULT_DUTY 10
#endif /* PWMOUTPUT_H_ */
