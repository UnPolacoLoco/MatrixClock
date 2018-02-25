// 
// 
// 

#include "Joystick.h"

//byte analogX: Analog port for X-axis || analogY: Analog port for Y-axis
Joystick::Joystick(byte analogX, byte analogY)
{
	analogPortX = analogX;
	analogPortY = analogY;
}

int Joystick::GetX()
{
	return analogRead(analogPortX);
}

int Joystick::GetY()
{
	return analogRead(analogPortY);
}

//sets new X position based on joystick movement relative to the currentX position reference
byte Joystick::SetRelativeX()
{
	if (GetX() > UPPER_DEADZONE && currentX != BOTTOM_X)
		return currentX--;
	else if (GetX() < LOWER_DEADZONE & currentX != UPPER_X)
		return currentX++;
	else
		return currentX;

}

//sets new Y position based on joystick movement relative to the currentX position reference
byte Joystick::SetRelativeY()
{
	if (GetY() > UPPER_DEADZONE && currentY != UPPER_Y)
		return currentY++;
	else if (GetY() < LOWER_DEADZONE && currentY != BOTTOM_Y)
		return currentY--;
	else
		return currentY;

}
