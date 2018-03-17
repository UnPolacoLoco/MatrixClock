// MatrixClock.h

#ifndef _MATRIXCLOCK_h
#define _MATRIXCLOCK_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

//DI pin for Matrix
#define MATRIX_PIN 2

//RTC pins
#define SCL A5
#define SDA A4

//Joystick pins
#define JOYSTICK_X A1
#define JOYSTICK_Y A2
#define JOYSTICK_BTTN 13

//increase when modes increase
#define NUM_OF_MODES 6




#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_GFX.h>
#include <Fonts\TomThumb.h>
#include <DS3231.h>
#include <EEPROM.h>
#include "Joystick.h"



class MatrixClock
{


public:

	enum MODES
	{
		TIME_AND_DATE,
		TIME,
		DATE,
		TEMPERATURE,
		CHANGE_COLOR,
		DEBUG,

	};

	typedef struct COLORS
	{

	};

	void initialize();

	void showDate();
	void showFullDate();
	void showTime();
	void showTemp();
	void showTimeAndDate();

	void drawDisplayBuffer();

	void changeTextColor();
	
	void scrollText(String textToScroll, int howFastToScroll = 150);
	void showText(String textToShow);

	void changeMode();
	const MODES getMode();


private:

	Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, 3, 1, MATRIX_PIN,
		NEO_TILE_TOP + NEO_TILE_LEFT + NEO_TILE_ROWS + NEO_TILE_PROGRESSIVE +
		NEO_MATRIX_BOTTOM + NEO_MATRIX_LEFT + NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
		NEO_GRB + NEO_KHZ800);

	DS3231 rtc = DS3231(A4, A5);

	Joystick joystick = Joystick(JOYSTICK_X, JOYSTICK_Y, JOYSTICK_BTTN);
	
	const uint8_t setAddress = 0x02; //Address of the set flag in the EEPROM

	int x = matrix.width(); // needed to scroll text on matrix

	String date;
	String temp;
	String time;

	uint8_t modeCounter = 0;

	uint16_t RED = matrix.Color(255, 0, 0);
	uint16_t GREEN = matrix.Color(0, 255, 0);
	uint16_t BLUE = matrix.Color(0, 0, 255);
	uint16_t YELLOW = matrix.Color(255, 255, 0);
	uint16_t CYAN = matrix.Color(0, 255, 255);
	uint16_t MAGENTA = matrix.Color(255, 0, 255);
	uint16_t WHITE = matrix.Color(255, 255, 255);
	uint16_t BLACK = matrix.Color(0, 0, 0);

	char displayBuffer[192];

};

#endif

