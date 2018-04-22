// Buzzer.h

#ifndef _BUZZER_h
#define _BUZZER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class Buzzer
{
public:
	Buzzer(uint8_t _pin);
	void alarm();
	void buzz();
private:
	uint8_t ALARM_FREQ = 80;
	uint8_t pin = 0;
};

#endif

