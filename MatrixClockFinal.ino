
#include "MatrixClock.h"
#include <Arduino.h>

MatrixClock clock;


void setup() 
{

	clock.initialize();

	pinMode(MATRIX_PIN, OUTPUT); //Data pin Arduino -> Matrix
	pinMode(JOYSTICK_BTTN, INPUT_PULLUP); //Joystick button, active low. 

	Serial.begin(115200);
}


void loop() 
{
	if (digitalRead(JOYSTICK_BTTN) == 0)
	{
		clock.changeMode();
	}

	clock.setBufferForTest();

	switch (clock.getMode())
	{

	case MODES::TIME_AND_DATE:
		Serial.println("In mode 0, Time and Date");
		clock.showTimeAndDate();
		break;

	case MODES::TIME:
		Serial.println("In mode 1, Just Time");
		clock.showTime();
		break;

	case MODES::DATE:
		Serial.println("In mode 2, Just Date");
		clock.showDate();
		break;

	case MODES::TEMPERATURE:

		Serial.println("in mode 3, Temperature");
		clock.showTemp();
		break;

		/*int previousX = joystick.GetCurrentX();
		int previousY = joystick.GetCurrentY();


		matrix.drawPixel(joystick.GetRelativeX(), joystick.GetRelativeY(), matrix.Color(0,255,0));
		matrix.show();

		if (joystick.previousX != joystick.GetCurrentX() || joystick.previousY != joystick.GetCurrentY())
		{
			delay(10);
			matrix.drawLine(joystick.previousX, joystick.previousY, joystick.previousX + (-joystick.GetMovementX() * 2), joystick.previousY + (-joystick.GetMovementY() * 2), matrix.Color(0,0,255));

		}

		matrix.show();*/
		
	


	case MODES::CHANGE_COLOR:
		Serial.println("in mode 4: change color");
		clock.changeTextColor();
		break;
	case MODES::CHANGE_BRIGHTNESS:
		Serial.println("in mode 5: change brightness");
		clock.changeBrightess();
		break;

	case MODES::DEBUG:
		Serial.println("in mode 6: debug");
		clock.drawDisplayBuffer();
	
		break;

	default:
		clock.showText("ERROR");
		break;
	}

}
