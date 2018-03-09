// 
// 
// 

#include "MatrixClock.h"


void MatrixClock::showDate()
{
	date = rtc.getDateStr();
	int lenght = date.length();
	
	scrollText(date);
}

void MatrixClock::showTime()
{
	switch (rtc.getTime().sec % 2)
		{
			
		case 0:
			time = rtc.getTime().hour;;
			time += " ";
			if (rtc.getTime().min < 10)
				time += "0";
			
			time += rtc.getTime().min;
			showText(time);
			break;
			
		case 1:
			time = rtc.getTime().hour;
			time += ":";
			if (rtc.getTime().min < 10)
				time += "0";
			time += rtc.getTime().min;
			showText(time);
			break;
		}
}

void MatrixClock::showTemp()
{
	if (joystick.GetMovementX() == 0)
	{
				
		temp = (int)rtc.getTemp();
		temp += "' C";
		showText(temp);
	}

	else
	{
		temp = (int)(rtc.getTemp() * 1.8 + 32);
		temp += "' F";
		showText(temp);
	}

}

void MatrixClock::changeTextColor()
{
	bool isEditing = true;
	uint8_t letter = 0;


	int newColor;

	while (isEditing)
	{
		letter += joystick.GetMovementX();
		delay(50);

		switch (letter % 3)
		{

		case 0: //editing RED
			Serial.println("editing RED");

			RED += joystick.GetMovementY() * -25;
			Serial.println(RED);
			newColor = matrix.Color(RED, GREEN, BLUE);
			matrix.setTextColor(newColor);
			showText("RED");
			delay(50);
			break;

		case 1: //editing GREEN
			Serial.println("editing GREEN");

			GREEN += joystick.GetMovementY() * -25;
			Serial.println(GREEN);
			newColor = matrix.Color(RED, GREEN, BLUE);

			matrix.setTextColor(newColor);
			showText("GREEN");
			delay(50);
			break;

		case 2: //editing BLUE
			Serial.println("editing BLUE");

			BLUE += joystick.GetMovementY() * -25;
			Serial.println(BLUE);
			newColor = matrix.Color(RED, GREEN, BLUE);
			matrix.setTextColor(newColor);
			showText("BLUE");
			delay(50);
			break;

		default:
			break;
		}

		if (digitalRead(JOYSTICK_BTTN) != 1)
		{
			delay(100);
			isEditing = false;
			modeCounter++;

		}
	}
}

void MatrixClock::initialize()
{
	rtc.begin();

	if (EEPROM.read(setAddress) != 1)
	{
		rtc.setDOW(THURSDAY);     // Set Day-of-Week to Thursday
		rtc.setTime(21, 00, 0);     // Set the time to 21:00:00 (24hr format)
		rtc.setDate(22, 2, 2018);   //Set date to 22nd of Feb, 2018
		EEPROM.write(setAddress, 1);
	}


	matrix.begin();
	matrix.setTextWrap(false);
	matrix.setBrightness(10);
	matrix.setTextColor(matrix.Color(255, 0, 0));
	matrix.setFont(&TomThumb);

}

void MatrixClock::changeMode()
{
	if(digitalRead(JOYSTICK_BTTN) != 1)
	{
		delay(200);
		modeCounter++;

	}
}

const uint8_t MatrixClock::getMode()
{
	return modeCounter % NUM_OF_MODES;
}

void MatrixClock::scrollText(String textToScroll)
{
	int lenght = textToScroll.length();

	matrix.fillScreen(0);
	matrix.setCursor(x, 7);
	matrix.print(textToScroll);

	if (--x < -lenght * 6) //the magic number (6) controls how many columns the text will scroll for. The longer the text, the more columns scrolled
	{
		x = matrix.width();
	}

	matrix.show();
	delay(100);
}

void MatrixClock::showText(String textToShow)
{
	
	int Cursor = matrix.width() / (textToShow.length() + 1);
	matrix.fillScreen(0);
	matrix.setCursor(Cursor, 7);
	matrix.print(textToShow);
	matrix.show();
	delay(50);
}
