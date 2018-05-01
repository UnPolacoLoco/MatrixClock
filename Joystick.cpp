// 
// 
// 

#include "Joystick.h"

Joystick::Joystick()
{
	//default ctor, remember to use assignsPins() to get the joystick up and running
}

Joystick::Joystick(int8_t analogX, int8_t analogY)
	: analogPortX(analogX), analogPortY(analogY)
{
	//constructor for joystick without a dedicated button
}

Joystick::Joystick(int8_t analogX, int8_t analogY, int8_t joystickButton) 
	: analogPortX(analogX), analogPortY(analogY), joystickButtonPort(joystickButton)
{
	//constructor for joystick with a dedicated button
}

int16_t Joystick::getAnalogX()
{
	return analogRead(analogPortX);
}

int16_t Joystick::getAnalogY()
{
	return analogRead(analogPortY);
}


int8_t Joystick::getMovementX()
{
	if (getAnalogX() > UPPER_DEADZONE)
		return -1;
	else if (getAnalogX() < LOWER_DEADZONE)
		return 1;
	else
		return 0;
}

int8_t Joystick::getMovementY()
{
	if (getAnalogY() > UPPER_DEADZONE)
		return 1;
	else if (getAnalogY() < LOWER_DEADZONE)
		return -1;
	else
		return 0;
}

bool Joystick::isPressed()
{
	return (digitalRead(joystickButtonPort) == 1 ? false : true);
}

void Joystick::assignPins(int8_t analogX, int8_t analogY, int8_t joystickButton)
{
	analogPortX = analogX;
	analogPortY = analogY;
	joystickButtonPort = joystickButton;
}
