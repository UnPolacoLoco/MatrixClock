// Joystick.h

#ifndef _JOYSTICK_h
#define _JOYSTICK_h

#define JOYSTICK_X A1
#define JOYSTICK_Y A2

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class Joystick
{
public:
	int GetX();
	int GetY();

	byte GetRelativeX(byte currentX);
	byte GetRelativeY();

};

#endif

