

#define MATRIX_PIN 5
#define SCL A5
#define SDA A4

#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#include <DS3231.h>







Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, 3, 1, MATRIX_PIN,
	NEO_TILE_TOP + NEO_TILE_LEFT + NEO_TILE_ROWS + NEO_TILE_PROGRESSIVE +
	NEO_MATRIX_BOTTOM + NEO_MATRIX_LEFT + NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
	NEO_GRB + NEO_KHZ800);

DS3231 rtc(SDA, SCL);



const int RED = matrix.Color(255, 0, 0);
const int GREEN = matrix.Color(0, 255, 0);
const int BLUE = matrix.Color(0, 0, 255);

byte mode = 0;
int x = matrix.width();

void setup() {
  // put your setup code here, to run once:
	matrix.begin();
	matrix.setTextWrap(false);
	matrix.setBrightness(10);
	matrix.setTextColor(GREEN);
	
	
	Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

	switch (mode)
	{
	case 0:
		Serial.println("in mode 0 - 24hr clock");
		matrix.fillScreen(0);
		matrix.setCursor(x, 0);
		matrix.print(F("Howdy"));
		if (--x < -36) {
			x = matrix.width();
		}
		matrix.show();
		delay(100);
		break;
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	}

}
