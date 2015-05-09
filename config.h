//*****************************************************************************
// config.h
//
// Created on: May 9, 2015
// Author: Nick
//*****************************************************************************

#ifndef CONFIG_H_
#define CONFIG_H_

//Define PWM Defaults & Constants
#define PWM_FREQ_HZ 150
#define PWM_DEFAULT_DUTY 10

//Define quadrature encoder defaults and constants
#define ENCODERSCALER 360 / 224  // Degrees per State Change

//Define altitude constants, such as mazimum and minimum value
#define MAX_ALT_ADC 1023 //650 for test rigs
#define MIN_ALT_ADC 0 //250 for test rigs
#define MAX_ALT_VOLTS 3300 //650 for test rigs
#define MIN_ALT_VOLTS 0 //250 for test rigs

#define MAX_ALT_PERCENT 100
#define MIN_ALT_PERCENT 0
//#define ALTITUDE_SCALE 100/400 //Convert the altitude measurement into a percentage value

//Define Altitude monitor settings
#define BUF_SIZE 10
#define ADC_SAMPLE_RATE_HZ 10

#endif /* CONFIG_H_ */
