//*****************************************************************************
// altitudeMonitorHome.h
//
// Created on: May 9, 2015
// Author: Nick
//*****************************************************************************

#ifndef ALTITUDEMONITORHOME_H_
#define ALTITUDEMONITORHOME_H_

#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/adc.h"
#include "altitudeMonitor.h"
#include "circBuf.h"

//Function Variables
circBuf_t g_AltitudeBuff;		    // Buffer of size BUF_SIZE integers (sample values)
unsigned long gul_AltitudeSampCnt;	// Counter for the interrupts

//Function prototypes
void Init_ADC(void);
void Altitude_Monitor_ISR(void);
void SysTickIntHandler(void);

#endif /* ALTITUDEMONITORHOME_H_ */
