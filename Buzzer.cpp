// 
// 
// 

#include "Buzzer.h"

Buzzer::Buzzer()
{

}

Buzzer::Buzzer(uint8_t _pin)
{
	pin = _pin;
}

void Buzzer::alarm()
{
	tone(pin, ALARM_FREQ, 333);
}

void Buzzer::buzz(uint8_t freq, uint8_t lenght)
{
	tone(pin, freq, lenght);
}

void Buzzer::assignPin(uint8_t _pin)
{
	pin = _pin;
}

