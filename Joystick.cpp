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
byte Joystick::SetRelativeX(byte& currentX)
{
	if (GetX() > UPPER_DEADZONE && currentX != 0)
		return currentX--;
	else if (GetX() < LOWER_DEADZONE & currentX != 23)
		return currentX++;
	else
		return currentX;

}

//sets new Y position based on joystick movement relative to the currentX position reference
byte Joystick::SetRelativeY(byte& currentY)
{
	if (GetY() > UPPER_DEADZONE && currentY != 7)
		return currentY++;
	else if (GetY() < LOWER_DEADZONE && currentY != 0)
		return currentY--;
	else
		return currentY;

}
