// 
// 
// 

#include "Buzzer.h"

Buzzer::Buzzer(uint8_t _pin)
{
	pin = _pin;
}

void Buzzer::alarm()
{
	tone(pin, ALARM_FREQ, 500);
}

void Buzzer::buzz(uint8_t freq)
{
	tone(pin, freq, 25);
}

