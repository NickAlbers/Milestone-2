/*
 * altitudeMonitor.h
 *
 *  Created on: May 8, 2015
 *      Author: Nick
 */

#ifndef ALTITUDEMONITOR_H_
#define ALTITUDEMONITOR_H_

//Includes
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
#include "stdio.h"
#include "stdint.h"
#include "circBuf.h"

//Function Prototypes
void Init_ADC(void);
void Altitude_Monitor_ISR(void);
void Sys_Tick_ISR(void);
void displayMeanVal(int meanVal, int count);
unsigned long Get_Alt(void);

//Constants
#define BUF_SIZE 100
#define SAMPLE_RATE_HZ 150

circBuf_t g_AltitudeBuff;		    // Buffer of size BUF_SIZE integers (sample values)
unsigned long gul_AltitudeSampCnt;	// Counter for the interrupts

#endif /* ALTITUDEMONITOR_H_ */
