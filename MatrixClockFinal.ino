
#include "Buzzer.h"
#include "MatrixClock.h"
#include <Arduino.h>

MatrixClock clock;

void setup() 
{

	clock.initialize();

	pinMode(MATRIX_PIN, OUTPUT); //Data pin Arduino -> Matrix
	pinMode(JOYSTICK_BTTN, INPUT_PULLUP); //Joystick button, active low. 
	pinMode(BUZZER, OUTPUT);

	Serial.begin(115200);
}


void loop() 
{
	if (digitalRead(JOYSTICK_BTTN) == 0)
	{
		clock.changeMode();
	}
	
	switch (clock.getMode())
	{

	case 0:
		Serial.println("In mode 0, Time and Date");
		clock.showTimeAndDate();
		break;

	/*case 1:
		Serial.println("In mode 1, Just Time");
		clock.showTime();
		break;*/

	//case 2:
	//	Serial.println("In mode 2, Just Date");
	//	clock.showDate();
	//	break;

	case 1:

		Serial.println("in mode 2, Temperature");
		clock.showTemp();
		break;

	case 2:
		Serial.println("in mode 3: change color");
		clock.changeTextColor();
		break;
	case 3:
		Serial.println("in mode 4: change brightness");
		clock.changeBrightess();
		break;

	case 4:
		Serial.println("in mode 5: Pong?");
		clock.PlayPong();
		break;

	default:
		clock.showText("ERROR");
		break;
	}

}
