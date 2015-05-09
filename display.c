//*****************************************************************************
// display.c
//
// Created on: May 10, 2015
// Author: Nick
//*****************************************************************************

#include "display.h"

//*****************************************************************************
// Initialise OLED display
//*****************************************************************************
void Init_Display (void)
{
	RIT128x96x4Init(1000000);
}

//*****************************************************************************
// Generic display function, takes an integer value, a metric, and the
// y position to disable the string at
//*****************************************************************************
void Display_Val (volatile int value, char* metric, int y_Pos)
{
	// Generate a string with the current passed value and display on the OLED
	// at the desired positon (X, Y, Level)

	char string [30];
	sprintf (string, "%s: %d     ", metric, value);
	RIT128x96x4StringDraw (string, 5, y_Pos, 15);
}


