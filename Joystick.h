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
	Joystick(int8_t analogX, int8_t analogY);

	//get current analog readings from Arduino analog ports
	int16_t GetAnalogX();
	int16_t GetAnalogY();

	//Gets currentX and Y positions (stored in the private variables)
	int8_t GetCurrentX();
	int8_t GetCurrentY();

	//sets the private variables currentX and currentY based on relative movement of the joystick
	int8_t SetRelativeX();
	int8_t SetRelativeY();

	//gets relative movement of the joystick on both axis, returns 1, -1 or 0
	int8_t GetRelativeX();
	int8_t GetRelativeY();



private:
	int8_t analogPortX; //Analog port for X-axis
	int8_t analogPortY; //Analog port for Y-axis

	int8_t currentX = 0;
	int8_t currentY = 0;

};

#endif
