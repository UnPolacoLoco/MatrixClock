// 
// 
// 

#include "MatrixClock.h"


void MatrixClock::initialize()
{
	rtc.begin();

	if (EEPROM.read(setAddress) != 1)
	{
		rtc.setDOW(THURSDAY);     // Set Day-of-Week to Thursday
		rtc.setTime(21, 00, 0);     // Set the time to 21:00:00 (24hr format)
		rtc.setDate(22, 2, 2018);   //Set date to 22nd of Feb, 2018
		EEPROM.write(setAddress, 1);
	}


	matrix.begin();
	matrix.setTextWrap(false);
	matrix.setBrightness(10);
	matrix.setTextColor(matrix.Color(255, 0, 0));
	matrix.setFont(&TomThumb);

	paddle1.startX = 0;
	paddle1.color = 'R';

	paddle2.startX = 23;
	paddle2.color = 'B';

	randomSeed(analogRead(A3));


	for (int i = 0; i < matrix.height(); i++)
	{
		for (int j = 0; j < matrix.width(); j++)
		{
			displayBuffer[i][j] = ' ';
		}
	}

	
}

#pragma region Displaying Text

void MatrixClock::scrollText(String textToScroll, int scrollSpeed = 150)
{
	int lenght = textToScroll.length();

	matrix.fillScreen(0);
	matrix.setCursor(x, 7);
	matrix.print(textToScroll);

	if (--x < -lenght * 5) //the magic number (5) controls how many columns the text will scroll for. The longer the text, the more columns scrolled
	{
		x = matrix.width();
	}

	matrix.show();
	delay(scrollSpeed);
}

void MatrixClock::showText(String textToShow)
{

	int Cursor = matrix.width() / (textToShow.length() + 1);
	matrix.fillScreen(0);
	matrix.setCursor(Cursor, 7);
	matrix.print(textToShow);
	matrix.show();
	delay(50);
}
#pragma endregion

#pragma region RTC Functionality


void MatrixClock::showDate()
{
	date = rtc.getDateStr();
	
	scrollText(date);
}

void MatrixClock::showFullDate()
{
	date = rtc.getDOWStr();
	date += ", ";
	date += rtc.getMonthStr();
	date += " ";
	date += rtc.getTime().date;

	if (rtc.getTime().date >= 10 && rtc.getTime().date <= 20)
	{
		date += "th";
	}

	else
	{
		switch (rtc.getTime().date % 10)
		{
		case 1:
			date += "st";
			break;
		case 2:
			date += "nd";
			break;
		case 3:
			date += "rd";
			break;
		default:
			date += "th";
			break;
		}
	}
		
	scrollText(date);
}

void MatrixClock::showTime()
{
	switch (rtc.getTime().sec % 2)
		{
			
		case 0:
			time = rtc.getTime().hour;;
			time += " ";
			if (rtc.getTime().min < 10)
				time += "0";
			
			time += rtc.getTime().min;
			showText(time);
			break;
			
		case 1:
			time = rtc.getTime().hour;
			time += ":";
			if (rtc.getTime().min < 10)
				time += "0";
			time += rtc.getTime().min;
			showText(time);
			break;
		}

}

void MatrixClock::showTemp()
{
	if (joystick.getMovementX() == 0)
	{
				
		temp = (int)rtc.getTemp();
		temp += "' C";
		showText(temp);
	}

	else
	{
		temp = (int)(rtc.getTemp() * 1.8 + 32);
		temp += "' F";
		showText(temp);
	}

}

void MatrixClock::showTimeAndDate()
{
	unsigned long currentTime = millis();
	bool modeChanged = false;

	while ((millis() - currentTime) < 25000 && !modeChanged) //show the time for 25000ms (25s)
	{
		showTime();
		modeChanged = joystick.isPressed();
	}

	currentTime = millis();
	x = matrix.width();

	while ((millis() - currentTime) < 16000 && !modeChanged) //it takes ~16000ms (16s) to scroll the entire FullDate()
	{
		showFullDate();
		modeChanged = joystick.isPressed();
	}

	if (modeChanged)
	{
		changeMode();
	}

}

#pragma endregion

void MatrixClock::drawDisplayBuffer()
{
	matrix.clear();

	

	for (int x = 0; x < 24; x++)
	{
		for(int y = 0; y < 8; y++)
		{ 
			switch (displayBuffer[x][y])
			{
			case 'R':
			case 'r':
				matrix.drawPixel(x, y, RED);
				break;
			case 'G':
			case 'g':
				matrix.drawPixel(x, y, GREEN);
				break;
			case 'B':
			case 'b':
				matrix.drawPixel(x, y, BLUE);
				break;
			case 'W':
			case 'w':
				matrix.drawPixel(x, y, WHITE);
				break;
			case 'C':
			case 'c':
				matrix.drawPixel(x, y, CYAN);
				break;
			case 'Y':
			case 'y':
				matrix.drawPixel(x, y, YELLOW);
				break;
			case 'M':
			case 'm':
				matrix.drawPixel(x, y, MAGENTA);
				break;

			default:
				matrix.drawPixel(x, y, BLACK);
				break;
			}
		}
		
		
	}

	matrix.show();
}

void MatrixClock::clearDisplayBuffer()
{

	for (int x = 0; x < 24; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			displayBuffer[x][y] = ' ';
		}
	}

}


void MatrixClock::changeTextColor()
{
	bool isEditing = true;
	uint8_t selectColor = 0;

	
	while (isEditing)
	{
		selectColor += joystick.getMovementX();
		delay(50);

		switch (selectColor % 7)
		{
		case 0:
			delay(50);
			matrix.setTextColor(RED);
			showText("RED");
			break;
		case 1:
			delay(50);
			matrix.setTextColor(GREEN);
			showText("GRN");
			break;
		case 2:
			delay(50);
			matrix.setTextColor(BLUE);
			showText("BLU");
			break;
		case 3:
			delay(50);
			matrix.setTextColor(WHITE);
			showText("WHT");
			break;
		case 4:
			delay(50);
			matrix.setTextColor(YELLOW);
			showText("YLW");
			break;

		case 5:
			delay(50);
			matrix.setTextColor(CYAN);
			showText("CYNN");
			break;

		case 6:
			delay(50);
			matrix.setTextColor(MAGENTA);
			showText("MGT");
			break;

			/*while (!joystick.IsPressed())
			{
				scrollText("Use up and down on joystick. Press the button when ready", 100);
			}

			

			switch (letter % 3)
			{

			case 0: //editing RED
				Serial.println("editing RED");

				_RED += joystick.GetMovementY() * -25;
				Serial.println(_RED);
				newColor = matrix.Color(_RED, _GREEN, _BLUE);
				matrix.setTextColor(newColor);
				showText("RED");
				delay(50);
				break;

			case 1: //editing GREEN
				Serial.println("editing GREEN");

				_GREEN += joystick.GetMovementY() * -25;
				Serial.println(_GREEN);
				newColor = matrix.Color(_RED, _GREEN, _BLUE);

				matrix.setTextColor(newColor);
				showText("GREEN");
				delay(50);
				break;

			case 2: //editing BLUE
				Serial.println("editing BLUE");

				_BLUE += joystick.GetMovementY() * -25;
				Serial.println(_BLUE);
				newColor = matrix.Color(_RED, _GREEN, _BLUE);
				matrix.setTextColor(newColor);
				showText("BLUE");
				delay(50);
				break;


			default:
				break;
			}

			*/

		default:
			break;

		}

		if (digitalRead(JOYSTICK_BTTN) != 1)
		{
			delay(100);
			isEditing = false;
			modeCounter++;

		}
	}
}

void MatrixClock::changeBrightess()
{
	bool isEditing = true;
	uint8_t brightness = matrix.getBrightness();
	delay(50);
	

	while (isEditing)
	{
		brightness -= joystick.getMovementY();
		brightness = constrain(brightness, 1, MAX_BRIGHTNESS);

		matrix.setBrightness(brightness);
		scrollText("BRIGHTNESS");

		if (joystick.isPressed())
		{
			delay(100);
			isEditing = false;
			modeCounter++;

		}
	}
}


void MatrixClock::changeMode()
{
	delay(200);
	modeCounter++;
}

const uint8_t MatrixClock::getMode()
{
	return modeCounter % NUM_OF_MODES;
}




#pragma region Pong




void MatrixClock::PlayPong()
{
	bool isPlaying = true;
	clearDisplayBuffer();
	drawDisplayBuffer();

	while (isPlaying)
	{
		//timing and input

		movePaddle(paddle1, joystick.getMovementY());
		movePaddle(paddle2, (random(0, 1023) > 512 ? -1 : 1));

		moveBall();
		delay(100);


		//game logic

		clearDisplayBuffer();
		updatePaddleLocation(paddle1);
		updatePaddleLocation(paddle2);
		updateBallLocation();
		didPaddleHitBall();

		//Display to player

		drawDisplayBuffer();

		//exit game logic
		if (joystick.isPressed())
		{
			String score;
			score += paddle1.score;
			score += "-";
			score += paddle2.score;
			showText(score);
			delay(2000);
			isPlaying = false;
			paddle1.score = 0;
			paddle2.score = 0;
			modeCounter++;

		}
	}
}

void MatrixClock::movePaddle(paddle& paddle, int8_t direction)
{
	//check whether the paddle is heading out of bounds
	if (paddle.paddleBlocks[0] + direction < 0 || paddle.paddleBlocks[1] + direction > 7) return;

	paddle.paddleBlocks[0] += direction;
	paddle.paddleBlocks[1] += direction;
	//paddle1.pongPaddle[2] += direction;
}

void MatrixClock::moveBall()
{

	if (ball.x + ball.momentumX > 23 || ball.x + ball.momentumX < 0)
	{
		ball.momentumX *= -1;

	}
	ball.x += ball.momentumX;

	if (ball.y + ball.momentumY > 7 || ball.y + ball.momentumY < 0)
	{
		ball.momentumY *= -1;

	}
	ball.y += ball.momentumY;



}

void MatrixClock::resetBall()
{
	ball.x = random(8, 15);
	ball.y = random(0, 7);
}

void MatrixClock::updatePaddleLocation(paddle& paddle) //draw paddle in the display buffer
{

	displayBuffer[paddle.startX][paddle.paddleBlocks[0]] = paddle.color;
	displayBuffer[paddle.startX][paddle.paddleBlocks[1]] = paddle.color;
	//displayBuffer[paddle.startX][paddle.pongPaddle[2]] = paddle.color;
}

void MatrixClock::updateBallLocation()
{
	displayBuffer[ball.x][ball.y] = 'W';
}

bool MatrixClock::didPaddleHitBall()
{
	//checks if the ball hits one of the parts of the player paddle
	if ((ball.y == paddle1.paddleBlocks[0] && ball.x == 1) ||
		(ball.y == paddle1.paddleBlocks[1] && ball.x == 1))
		// ||(ball.y == paddle1.pongPaddle[2] && ball.x == 1))
	{
		ball.momentumX = 1;
		return true;
	}

	//check to see if the ball hits the player paddle diagonally from top right
	else if ((ball.momentumY > 0 && ball.y == (paddle1.paddleBlocks[0] - 1) && ball.x == 1))
	{
		ball.momentumX = 1;
		ball.momentumY *= -1;
		return true;
	}

	//check to see if the ball hits the player paddle diagonally from bottom right
	else if ((ball.momentumY < 0 && ball.y == (paddle1.paddleBlocks[1] + 1) && ball.x == 1))
	{
		ball.momentumX = 1;
		ball.momentumY *= -1;
		return true;
	}

	else if ((ball.y == paddle2.paddleBlocks[0] && ball.x == 22) ||
		(ball.y == paddle2.paddleBlocks[1] && ball.x == 22))
		// || (ball.y == paddle2.pongPaddle[2] && ball.x == 22))
	{
		ball.momentumX = -1;
		return true;
	}

	else if (ball.x <= 0)
	{
		paddle2.score++;
		resetBall();
		delay(100);
		return false;
	}
	else if (ball.x >= 23)
	{
		paddle1.score++;
		resetBall();
		delay(100);
		return false;
	}
}
#pragma endregion
