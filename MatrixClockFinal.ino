
#include "Joystick.h"
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#include <DS3231.h>
#include <Arduino.h>
#include <EEPROM.h>
#include <Fonts\TomThumb.h>
#include <WString.h>

#define MATRIX_PIN 2

#define NUM_OF_MODES 5
#define OUT

#define SCL A5
#define SDA A4

#define JOYSTICK_X A1
#define JOYSTICK_Y A2
#define JOYSTICK_BTTN 13

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, 3, 1, MATRIX_PIN,
	NEO_TILE_TOP + NEO_TILE_LEFT + NEO_TILE_ROWS + NEO_TILE_PROGRESSIVE +
	NEO_MATRIX_BOTTOM + NEO_MATRIX_LEFT + NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
	NEO_GRB + NEO_KHZ800);


DS3231 rtc(SDA, SCL);
Joystick joystick = Joystick(JOYSTICK_X, JOYSTICK_Y);



const int RED = matrix.Color(255, 0, 0);
const int GREEN = matrix.Color(0, 255, 0);
const int BLUE = matrix.Color(0, 0, 255);

volatile byte mode = 0;
byte setAddress = 0x02; //Address of the set flag in the EEPROM

int x = matrix.width();

//strings needed to work with the Real Time Clock
String temp;
String date;
String time;

byte modeCounter = 0;
void changeMode()
{
	if (digitalRead(JOYSTICK_BTTN) != 1)
	{
		delay(200);
		modeCounter++;

	}
}

//scroll text on the matrix from right to left. See Adafruit Print function for all possible types of arguments
template<typename T> scrollTextOnMatrix(T text, int textLenght = 0) 
{
	matrix.fillScreen(0);
	matrix.setCursor(x, 7);
	matrix.print(text);
	if (--x < -textLenght*6) //the magic number (6) controls how many columns the text will scroll for. The longer the text, the more columns scrolled
	{
		x = matrix.width();
	}
	matrix.show();
	delay(100);
}

//show text on matrix without scrolling, cursor position can be manipulate with the lenght of 'text'. You have to know/calculate text lenght. defaults to matrix.width(), which will give cursor starting position at 0
template <typename T> showTextOnMatrix(T text, int textLenght = matrix.width()) 
{
	int Cursor = matrix.width() / (textLenght + 1);
	matrix.fillScreen(0);
	matrix.setCursor(Cursor, 7);
	matrix.print(text);
	matrix.show();
	delay(50);
}



void setup() {

	//matrix initialization
	matrix.begin();
	matrix.setTextWrap(false);
	matrix.setBrightness(10);
	matrix.setTextColor(BLUE);
	matrix.setFont(&TomThumb);

	//real time clock module initialization
	rtc.begin();
	if(EEPROM.read(setAddress) != 1)
	{ 
		rtc.setDOW(THURSDAY);     // Set Day-of-Week to Thursday
		rtc.setTime(21, 00, 0);     // Set the time to 21:00:00 (24hr format)
		rtc.setDate(22, 2, 2018);   //Set date to 22nd of Feb, 2018
		EEPROM.write(setAddress, 1);
	}

	pinMode(MATRIX_PIN, OUTPUT); //Data pin Arduino -> Matrix
	pinMode(JOYSTICK_BTTN, INPUT_PULLUP); //Joystick button, active low. 
	
	Serial.begin(115200);
}
int8_t previousX;
int8_t previousY;


void loop() {

	changeMode();
	


	switch (modeCounter % NUM_OF_MODES)
	{
	
	case 0:
		Serial.println("in mode 0 - 24hr clock");

		switch (rtc.getTime().sec % 2)
		{
		
		case 0:
			time = rtc.getTime().hour;;
			time += " ";
			if (rtc.getTime().min < 10)
				time += "0";
		
			time += rtc.getTime().min;
			showTextOnMatrix(time, time.length());
			break;
		
		case 1:
			time = rtc.getTime().hour;
			time += ":";
			if (rtc.getTime().min < 10)
				time += "0";
			time += rtc.getTime().min;
			showTextOnMatrix(time, time.length());
			break;
		}


		break;

	case 1:
		Serial.println("in mode 1 - date");

		date = rtc.getDateStr();
		scrollTextOnMatrix(date, date.length());

		break;

	case 2:
		Serial.println("In mode 2, Temperature");

		temp = (int)rtc.getTemp();
		temp += "' C";
		showTextOnMatrix(temp, temp.length());

		break;


	case 3:
		Serial.println("in mode 3, relative joystick control test");

		matrix.fillScreen(0);

		previousX = joystick.GetCurrentX();
		previousY = joystick.GetCurrentY();

		

		matrix.drawPixel(joystick.SetRelativeX(), joystick.SetRelativeY(), GREEN);
		matrix.show();

		if (previousX != joystick.GetCurrentX() || previousY != joystick.GetCurrentY())
		{
			delay(10);
			matrix.drawLine(previousX, previousY, previousX + (-joystick.GetRelativeX() * 2), previousY + (-joystick.GetRelativeY() * 2), RED);

		}
		matrix.show();
		delay(10);

		break;

	case 4:

		Serial.println("in mode 4: change color");

		bool isEditing = true;
		int8_t letter = 0;
		int8_t newBlue = 255;
		int8_t newRed = 255;
		int8_t newGreen = 0;

		int newColor;

		while (isEditing)
		{
			letter += joystick.GetRelativeX();
			showTextOnMatrix("R G B", 5);
			delay(50);

			switch (letter % 3)
			{
				
			case 0: //editing RED
				Serial.println("editing RED");
				Serial.println(joystick.GetRelativeY());
				newRed += joystick.GetRelativeY();
				newColor = matrix.Color(newRed, newGreen, newBlue);
				matrix.setTextColor(newColor);
				showTextOnMatrix("   G B", 5);
				delay(50);
				break;
			case 1: //editing GREEN
				Serial.println("editing GREEN");
				Serial.println(joystick.GetRelativeY());
				newGreen += joystick.GetRelativeY();
				newColor = matrix.Color(newRed, newGreen, newBlue);
				matrix.setTextColor(newColor);
				showTextOnMatrix("R    B", 5);
				delay(50);
				break;
			case 2: //editing BLUE
				Serial.println("editing BLUE");
				Serial.println(joystick.GetRelativeY());
				newBlue += joystick.GetRelativeY();
				newColor = matrix.Color(newRed, newGreen, newBlue);
				matrix.setTextColor(newColor);
				showTextOnMatrix("R G   ", 5);
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


		break;

		
	}

}
