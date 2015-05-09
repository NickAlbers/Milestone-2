// *******************************************************
//
// quadEncoder.h
//
// Support for quadrature encoding on the Stellaris LM3S1968 EVK
// N.C. Albers UCECE
// Last modified:  5.5.2015
//
// *******************************************************

#ifndef YAW_ENCODER_H_
#define YAW_ENCODER_H_
#define ENCODERSCALER 360 / 224  // Degrees per State Change

#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "drivers/rit128x96x4.h"
#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"

volatile static int16_t yawAngle = 0;

int16_t Get_Yaw(void);
void Init_Pins (void);
void Init_Ref_Pin (void);
void Init_Quad_Decoder (void);
void Quad_Decoder_ISR (void);
void Display_Val (volatile int16_t value, char* metric, int y_Pos);

#endif /* YAW_ENCODER_H_ */
