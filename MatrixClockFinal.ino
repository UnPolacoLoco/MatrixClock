
#include "SpecialDays.h"
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
		clock.showTimeAndDate();
		break;

	case 1:
		clock.showTemp();
		break;

	case 2:
		clock.changeTextColor();
		break;

	case 3:
		clock.changeBrightess();
		break;

	case 4:
		clock.PlayPong();
		break;

	case 5:
		clock.changeTime();
		break;

	default:
		clock.showText("ERROR");
		break;
	}

}
