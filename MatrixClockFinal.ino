
#define MATRIX_PIN 2
#define JOYSTICK_BTTN 3
#define SCL A5
#define SDA A4

#define NUM_OF_MODES 3

#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#include <DS3231.h>
#include <Arduino.h>
#include <EEPROM.h>
#include <Fonts\TomThumb.h>
#include <WString.h>


Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, 3, 1, MATRIX_PIN,
	NEO_TILE_TOP + NEO_TILE_LEFT + NEO_TILE_ROWS + NEO_TILE_PROGRESSIVE +
	NEO_MATRIX_BOTTOM + NEO_MATRIX_LEFT + NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
	NEO_GRB + NEO_KHZ800);

DS3231 rtc(SDA, SCL);




const int RED = matrix.Color(255, 0, 0);
const int GREEN = matrix.Color(0, 255, 0);
const int BLUE = matrix.Color(0, 0, 255);

volatile byte mode = 0;
byte setAddress = 0x02; //Address of the set flag in the EEPROM
int x = matrix.width();

String temp;
String date;
String time;

void changeMode()
{
	mode++;
}

template<typename T> scrollTextOnMatrix(T text, int textLenght = 0) //scroll text on the matrix from right to left. See Adafruit Print function for all possible types of arguments
{
	Serial.println(textLenght);
	matrix.fillScreen(0);
	matrix.setCursor(x, 7);
	matrix.print(text);
	if (--x < -textLenght*6) {
		x = matrix.width();
	}
	matrix.show();
	delay(100);
}

template <typename T> showTextOnMatrix(T text, int textLenght = matrix.width()) //show text on matrix without scrolling, cursor position can be manipulate with the lenght of 'text'. You have to know/calculate text lenght. defaults to matrix.width(), which will give cursor starting position at 0
{
	

	int Cursor = matrix.width() / (textLenght + 1);
	matrix.fillScreen(0);
	matrix.setCursor(Cursor, 7);
	matrix.print(text);
	matrix.show();
	delay(100);
}



void setup() {
  // put your setup code here, to run once:
	matrix.begin();
	matrix.setTextWrap(false);
	matrix.setBrightness(10);
	matrix.setTextColor(BLUE);
	matrix.setFont(&TomThumb);

	rtc.begin();
	if(EEPROM.read(setAddress) != 1)
	{ 
		rtc.setDOW(THURSDAY);     // Set Day-of-Week to Thursday
		rtc.setTime(21, 00, 0);     // Set the time to 21:00:00 (24hr format)
		rtc.setDate(22, 2, 2018);   //Set date to 22nd of Feb, 2018
		EEPROM.write(setAddress, 1);
	}

	pinMode(MATRIX_PIN, OUTPUT); //Data pin Arduino -> Matrix
	pinMode(JOYSTICK_BTTN, INPUT_PULLUP); //Joystick button. 

	
	attachInterrupt(digitalPinToInterrupt(JOYSTICK_BTTN), changeMode, RISING);

	
	
	Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:


	switch (mode % NUM_OF_MODES)
	{
	
	case 0:
		Serial.println("in mode 0 - 24hr clock");

		time = rtc.getTimeStr();
		scrollTextOnMatrix(time, time.length());

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

	}

}
