//*****************************************************************************
// altitudeMonitor.c
//
// Created on: May 8, 2015
// Author: Nick
//*****************************************************************************

#include "altitudeMonitor.h"

//*****************************************************************************
// Initialise ADC0
//*****************************************************************************

void Init_ADC(void)
{

	// Initialise ADC0 on Port B for use
	SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);

	// Initiliase ADC0 speed, options are 1MSPS, 250KSPS, 125KSPS

	// Enable sample sequence 3 with a timer trigger.
	ADCSequenceConfigure(ADC0_BASE, 3, ADC_TRIGGER_PROCESSOR, 0);
	ADCSequenceStepConfigure(ADC0_BASE, 3, 0, ADC_CTL_CH0 | ADC_CTL_IE |
	                             ADC_CTL_END);

	// Since sample sequence 3 is now configured, it must be enabled.
	ADCSequenceEnable(ADC0_BASE, 3);

	// Register the interrupt handler
	ADCIntRegister (ADC0_BASE, 3, Altitude_Monitor_ISR);

	// Enable interrupts for ADC0 sequence 3 (clears any outstanding interrupts)
	ADCIntEnable(ADC0_BASE, 0);
}

//*****************************************************************************
//The Interrupt handler for the Altitude Monitor
//*****************************************************************************
void Altitude_Monitor_ISR(void)
{
	unsigned long ulValue;

	//Get a single sample from ADC0
	ADCSequenceDataGet(ADC0_BASE, 3, &ulValue);

	//Place it in a circular buffer and advance write index
	//ul_AltitudeVal = (int) ulValue;
	g_AltitudeBuff.data[g_AltitudeBuff.windex] = (int) ulValue;
	g_AltitudeBuff.windex ++;
	if (g_AltitudeBuff.windex >= g_AltitudeBuff.size)
		g_AltitudeBuff.windex = 0;

	// Clear the interrupt
	ADCIntClear(ADC0_BASE,3);
}

//*****************************************************************************
// The interrupt handler for the for SysTick interrupt.
//*****************************************************************************
void Sys_Tick_ISR(void)
{
    //
    // Initiate a conversion
    //
    ADCProcessorTrigger(ADC0_BASE, 3);
    gul_AltitudeSampCnt++;
}



//unsigned long Get_Alt()
//{
//	return (ul_AltitudeVal); // Placeholder value until ADC functions
//}
