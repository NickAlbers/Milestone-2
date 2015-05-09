//*****************************************************************************
// display.h
//
// Created on: May 10, 2015
// Author: Nick
//*****************************************************************************

#ifndef DISPLAY_H_
#define DISPLAY_H_

// Includes
#include "drivers/rit128x96x4.h"
#include "stdlib.h"
#include "stdio.h"

//Function prototypes
void Init_Display (void);
void Display_Val (volatile int value, char* metric, int y_Pos);

#endif /* DISPLAY_H_ */
