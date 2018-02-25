// Joystick.h

#ifndef _JOYSTICK_h
#define _JOYSTICK_h



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

	byte SetRelativeX(byte& currentX);
	byte SetRelativeY(byte& currentY);

private:
	byte joystickX; //Analog port for X-axis
	byte joystickY; //Analog port for Y-axis

};

#endif

