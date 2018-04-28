
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

#ifdef DEBUG
	Serial.begin(115200);
#endif // DEBUG

	
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
#ifdef DEBUG
		Serial.println("In mode 0, Time and Date");
#endif // DEBUG
		clock.showTimeAndDate();
		break;

	case 1:
#ifdef DEBUG
		Serial.println("in mode 1, Temperature");
#endif // DEBUG
		clock.showTemp();
		break;

	case 2:
#ifdef DEBUG
		Serial.println("in mode 2: change color");
#endif // DEBUG
		clock.changeTextColor();
		break;

	case 3:
#ifdef DEBUG
		Serial.println("in mode 3: change brightness");
#endif // DEBUG
		clock.changeBrightess();
		break;

	case 4:
#ifdef DEBUG
		Serial.println("in mode 4: PONG");
#endif // DEBUG
		clock.PlayPong();
		break;

	default:
		clock.showText("ERROR");
		break;
	}

}
