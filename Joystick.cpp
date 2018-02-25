// 
// 
// 

#include "Joystick.h"

Joystick::Joystick(byte analogX, byte analogY)
{
	joystickX = analogX;
	joystickY = analogY;
}

int Joystick::GetX()
{
	return analogRead(joystickX);
}

int Joystick::GetY()
{
	return analogRead(joystickY);
}

//sets new X position based on joystick movement relative to the currentX position reference
byte Joystick::SetRelativeX(byte& currentX)
{
	if (GetX() > 700 && currentX != 0)
		return currentX--;
	else if (GetX() < 300 & currentX != 23)
		return currentX++;
	else
		return currentX;

}

//sets new Y position based on joystick movement relative to the currentX position reference
byte Joystick::SetRelativeY(byte& currentY)
{
	if (GetY() > 700 && currentY != 7)
		return currentY++;
	else if (GetY() < 300 && currentY != 0)
		return currentY--;
	else
		return currentY;

}
