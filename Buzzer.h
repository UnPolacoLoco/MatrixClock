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
	Buzzer();
	Buzzer(uint8_t _pin);

	void alarm();
	void buzz(uint8_t freq = 50, uint8_t lenght = 25);
	void assignPin(uint8_t _pin);

private:
	uint8_t ALARM_FREQ = 70;
	uint8_t pin = 0;
};

#endif

