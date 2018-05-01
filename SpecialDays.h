// SpecialDays.h

#ifndef _SPECIALDAYS_h
#define _SPECIALDAYS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


class SpecialDays
{
public:
	SpecialDays(uint8_t _day, uint8_t _month, uint16_t _year, String _message);
	uint8_t getDay();
	uint8_t getMonth();
	uint16_t getYear();
	String getMessage();



private:
	uint8_t day = 0;
	uint8_t month = 0;
	int year = 0;
	const String message = "";
	
};

#endif

