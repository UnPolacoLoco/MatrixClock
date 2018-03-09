
#include "MatrixClock.h"
#include <Arduino.h>


#define NUM_OF_MODES 5
#define OUT


MatrixClock clock;





void setup() {



	clock.initialize();

	pinMode(MATRIX_PIN, OUTPUT); //Data pin Arduino -> Matrix
	pinMode(JOYSTICK_BTTN, INPUT_PULLUP); //Joystick button, active low. 

	Serial.begin(115200);
}


void loop() {

	clock.changeMode();
	
	//clock.showDate();
	//clock.showTime();
	//clock.showTemp();

	switch (clock.getMode() % NUM_OF_MODES)
	{
	
	case 0:
		Serial.println("In mode 0, Time");
		clock.showTime();
		break;

	case 1:
		Serial.println("In mode 1, Date");
		clock.showDate();
		break;

	case 2:
		Serial.println("In mode 2, Temperature");
		clock.showTemp();
		break;

	case 3:
		break;
		/*Serial.println("in mode 3, relative joystick control test");


		joystick.previousX = joystick.GetCurrentX();
		joystick.previousY = joystick.GetCurrentY();


		matrix.drawPixel(joystick.GetRelativeX(), joystick.GetRelativeY(), matrix.Color(0,255,0));
		matrix.show();

		if (joystick.previousX != joystick.GetCurrentX() || joystick.previousY != joystick.GetCurrentY())
		{
			delay(10);
			matrix.drawLine(joystick.previousX, joystick.previousY, joystick.previousX + (-joystick.GetMovementX() * 2), joystick.previousY + (-joystick.GetMovementY() * 2), matrix.Color(0,0,255));

		}

		matrix.show();
		delay(10);

		break;*/

	case 4:

		Serial.println("in mode 4: change color");
		clock.changeTextColor();
		break;

		
	}

}
