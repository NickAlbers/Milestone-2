//*****************************************************************************
// altitudeMonitorHome.c
//
// Created on: May 9, 2015
// Author: Nick
//*****************************************************************************

#include "altitudeMonitor.h"

//*****************************************************************************
// Initialise ADC
//*****************************************************************************

void Init_ADC(void)
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
	ADCSequenceConfigure(ADC0_BASE, 3, ADC_TRIGGER_PROCESSOR, 0);
	ADCSequenceStepConfigure(ADC0_BASE, 3, 0, ADC_CTL_CH0 | ADC_CTL_IE |
	                             ADC_CTL_END);
	ADCSequenceEnable(ADC0_BASE, 3);
	ADCIntRegister (ADC0_BASE, 3, Altitude_Monitor_ISR);
	ADCIntEnable(ADC0_BASE, 3);
}

//*****************************************************************************
//The Interrupt handler for the Altitude Monitor
//*****************************************************************************

void Altitude_Monitor_ISR(void)
{
	unsigned long ulValue;
	static int altitudeworking = 0;

	//Get a single sample from ADC0
	ADCSequenceDataGet(ADC0_BASE, 3, &ulValue);

	//Place it in a circular buffer and advance write index
	altitudeworking ++;
//	ul_AltitudeVal = (int) ulValue;
	g_AltitudeBuff.data[g_AltitudeBuff.windex] = (int) ulValue;
	g_AltitudeBuff.windex ++;
	if (g_AltitudeBuff.windex >= g_AltitudeBuff.size)
		g_AltitudeBuff.windex = 0;

	// Clear the interrupt
	ADCIntClear(ADC0_BASE, 3);

}


//*****************************************************************************
//The Interrupt handler for the Systick Timer
//*****************************************************************************

void SysTickIntHandler(void)
{
    // Initiate a conversion
    ADCProcessorTrigger(ADC0_BASE, 3);
    gul_AltitudeSampCnt++;
}


