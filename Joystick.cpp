// 
// 
// 

#include "Joystick.h"

//byte analogX: Analog port for X-axis || analogY: Analog port for Y-axis
Joystick::Joystick(int8_t analogX, int8_t analogY)
{
	analogPortX = analogX;
	analogPortY = analogY;
}

int16_t Joystick::GetAnalogX()
{
	return analogRead(analogPortX);
}

int16_t Joystick::GetAnalogY()
{
	return analogRead(analogPortY);
}

int8_t Joystick::GetCurrentX()
{
	return currentX;
}

int8_t Joystick::GetCurrentY()
{
	return currentY;
}

//sets new X position based on joystick movement relative to the currentX position reference
int8_t Joystick::GetRelativeX()
{
	if (currentX + GetMovementX() >= BOTTOM_X && currentX + GetMovementX() <= UPPER_X)
	return currentX += GetMovementX();
}

//sets new Y position based on joystick movement relative to the currentX position reference
int8_t Joystick::GetRelativeY()
{
	if (currentY + GetMovementY() >= BOTTOM_Y && currentY + GetMovementY() <= UPPER_Y)
	return currentY += GetMovementY();
}

int8_t Joystick::GetMovementX()
{
	if (GetAnalogX() > UPPER_DEADZONE)
		return -1;
	else if (GetAnalogX() < LOWER_DEADZONE)
		return 1;
	else
		return 0;
}

int8_t Joystick::GetMovementY()
{
	if (GetAnalogY() > UPPER_DEADZONE)
		return 1;
	else if (GetAnalogY() < LOWER_DEADZONE)
		return -1;
	else
		return 0;
}
