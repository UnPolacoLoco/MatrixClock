// Joystick.h

#ifndef _JOYSTICK_h
#define _JOYSTICK_h

#define UPPER_DEADZONE 650
#define LOWER_DEADZONE 250

#define BOTTOM_X 0
#define BOTTOM_Y 0
#define UPPER_X 23
#define UPPER_Y 7

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class Joystick
{

public:
	Joystick(byte analogX, byte analogY);

	int GetX();
	int GetY();

	byte SetRelativeX();
	byte SetRelativeY();

private:
	byte analogPortX; //Analog port for X-axis
	byte analogPortY; //Analog port for Y-axis

	byte currentX = 0;
	byte currentY = 0;

};

#endif

