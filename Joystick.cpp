// 
// 
// 

#include "Joystick.h"

int Joystick::GetX()
{
	return analogRead(JOYSTICK_X);
}

int Joystick::GetY()
{
	return analogRead(JOYSTICK_Y);
}
