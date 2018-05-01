// 
// 
// 

#include "SpecialDays.h"

SpecialDays::SpecialDays(uint8_t _day, uint8_t _month, uint16_t _year, const String _message)
	: day(_day), month(_month), year(_year), message(_message)
{

}

uint8_t SpecialDays::getDay()
{
	return day;
}

uint8_t SpecialDays::getMonth()
{
	return month;
}

uint16_t SpecialDays::getYear()
{
	return year;
}

String SpecialDays::getMessage()
{
	return message;
}
