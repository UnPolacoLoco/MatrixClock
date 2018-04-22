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
	tone(pin, ALARM_FREQ, 250);
}

void Buzzer::buzz()
{
	tone(pin, 50, 25);
}

