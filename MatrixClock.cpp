// 
// 
// 

#include "MatrixClock.h"


void MatrixClock::showDate()
{
	date = rtc.getDateStr();
	
	scrollText(date);
}

void MatrixClock::showFullDate()
{
	date = rtc.getDOWStr();
	date += ", ";
	date += rtc.getMonthStr();
	date += " ";
	date += rtc.getTime().date;

	if (rtc.getTime().date >= 10 && rtc.getTime().date <= 20)
	{
		date += "th";
	}
	else
	{
		switch (rtc.getTime().date % 10)
		{
		case 1:
			date += "st";
			break;
		case 2:
			date += "nd";
			break;
		case 3:
			date += "rd";
			break;
		default:
			date += "th";
			break;
		}
	}
		
	
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

void MatrixClock::showTimeAndDate()
{
	unsigned long currentTime = millis();
	bool modeChanged = false;

	while ((millis() - currentTime) < 10000 && !modeChanged) //show the clock for 10000ms (10s)
	{
		showTime();
		modeChanged = joystick.IsPressed();
	}

	currentTime = millis();
	x = matrix.width();

	while ((millis() - currentTime) < 16000 && !modeChanged) //it takes 16000ms (16s) to scroll the entire FullDate()
	{
		showFullDate();
		modeChanged = joystick.IsPressed();
	}

	if (modeChanged)
	{
		changeMode();
	}

}

void MatrixClock::drawDisplayBuffer()
{
	matrix.clear();

	int8_t x = 0;
	int8_t y = 0;
	


	for (int i = 0; i < matrix.numPixels(); i++)
	{
		x = i % matrix.width();
		y = i / matrix.width();
		
		switch (displayBuffer[i])
		{
		case 'R':
		case 'r':
			matrix.drawPixel(x, y, RED);
			break;
		case 'G':
		case 'g':
			matrix.drawPixel(x, y, GREEN);
			break;
		case 'B':
		case 'b':
			matrix.drawPixel(x, y, BLUE);
			break;
		case 'W':
		case 'w':
			matrix.drawPixel(x, y, WHITE);
			break;
		case 'C':
		case 'c':
			matrix.drawPixel(x, y, CYAN);
			break;
		case 'Y':
		case 'y':
			matrix.drawPixel(x, y, YELLOW);
			break;
		case 'M':
		case 'm':
			matrix.drawPixel(x, y, MAGENTA);
			break;

		default:
			matrix.drawPixel(x, y, BLACK);
			break;
		}
		
		
	}

	matrix.show();
}

void MatrixClock::changeTextColor()
{
	bool isEditing = true;
	uint8_t letter = 0;

	uint16_t _RED = RED;
	uint16_t _GREEN = RED;
	uint16_t _BLUE = RED;

	uint16_t newColor = _RED;

	while (!joystick.IsPressed())
	{
		scrollText("Use up and down on joystick. Press the button when ready", 100);
	}

	while (isEditing)
	{
		letter += joystick.GetMovementX();
		delay(50);

		switch (letter % 3)
		{

		case 0: //editing RED
			Serial.println("editing RED");

			_RED += joystick.GetMovementY() * -25;
			Serial.println(_RED);
			newColor = matrix.Color(_RED, _GREEN, _BLUE);
			matrix.setTextColor(newColor);
			showText("RED");
			delay(50);
			break;

		case 1: //editing GREEN
			Serial.println("editing GREEN");

			_GREEN += joystick.GetMovementY() * -25;
			Serial.println(_GREEN);
			newColor = matrix.Color(_RED, _GREEN, _BLUE);

			matrix.setTextColor(newColor);
			showText("GREEN");
			delay(50);
			break;

		case 2: //editing BLUE
			Serial.println("editing BLUE");

			_BLUE += joystick.GetMovementY() * -25;
			Serial.println(_BLUE);
			newColor = matrix.Color(_RED, _GREEN, _BLUE);
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

	int counter = 0;

	for (int i = 0; i < 192; i++)
	{
		switch (counter % 3)
		{
		case 0:
			displayBuffer[i] = 'R';
			break;
		case 1:
			displayBuffer[i] = 'G';
			break;
		case 2:
			displayBuffer[i] = 'B';
			break;
		}

		counter++;
	}

}

void MatrixClock::changeMode()
{
	delay(200);
	modeCounter++;
}

const MatrixClock::MODES MatrixClock::getMode()
{
	switch (modeCounter % NUM_OF_MODES)
	{
	case 0:
		return MODES::TIME_AND_DATE;
		break;
	case 1:
		return MODES::TIME;
		break;
	case 2:
		return MODES::DATE;
		break;
	case 3:
		return MODES::TEMPERATURE;
		break;
	case 4:
		return MODES::CHANGE_COLOR;
		break;
	case 5:
		return MODES::DEBUG;
		break;

	}
}

void MatrixClock::scrollText(String textToScroll, int scrollSpeed = 150)
{
	int lenght = textToScroll.length();

	matrix.fillScreen(0);
	matrix.setCursor(x, 7);
	matrix.print(textToScroll);

	if (--x < -lenght * 5) //the magic number (5) controls how many columns the text will scroll for. The longer the text, the more columns scrolled
	{
		x = matrix.width();
	}

	matrix.show();
	delay(scrollSpeed);
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
