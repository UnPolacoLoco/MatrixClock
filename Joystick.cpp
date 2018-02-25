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

byte Joystick::GetRelativeX(byte currentX)
{
	if (GetX() > 700 && currentX != 0)
		return currentX - 1;
	else if (GetX() < 300 & currentX != 23)
		return currentX + 1;
	else
		return currentX;

}
