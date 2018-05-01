// Joystick.h

#ifndef _JOYSTICK_h
#define _JOYSTICK_h

#define UPPER_DEADZONE 650
#define LOWER_DEADZONE 250

#define BOTTOM_X 0
#define UPPER_X 23

#define BOTTOM_Y 0
#define UPPER_Y 7



#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class Joystick
{

public:
	Joystick();
	Joystick(int8_t analogX, int8_t analogY);
	Joystick(int8_t analogX, int8_t analogY, int8_t joystickButton);

	//get current analog readings from Arduino analog ports
	int16_t getAnalogX();
	int16_t getAnalogY();

	//gets relative movement of the joystick on both axis, returns 1, -1 or 0
	int8_t getMovementX();
	int8_t getMovementY();

	//reads digital port and returns true if button is pressed at the time of polling.
	bool isPressed();
	
	void assignPins(int8_t analogX, int8_t analogY, int8_t joystickButton);



private:
	int8_t analogPortX; //Analog port for X-axis
	int8_t analogPortY; //Analog port for Y-axis
	int8_t joystickButtonPort; //Digital port for joystickButton

};

#endif

