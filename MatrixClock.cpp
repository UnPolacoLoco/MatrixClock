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
	matrix.setTextColor(BLUE);
	matrix.setFont(&TomThumb);

	paddle1.startX = 0;
	paddle1.color = 'R';

	paddle2.startX = 23;
	paddle2.color = 'B';

	ball2.momentumX = 1;
	ball2.color = 'G';

	randomSeed(analogRead(A3));


	clearDisplayBuffer();
	
}

#pragma region Displaying Text

void MatrixClock::scrollText(const String& textToScroll, int scrollSpeed = 150)
{
	int lenght = textToScroll.length();

	matrix.fillScreen(0);
	matrix.setCursor(x, 7);
	matrix.print(textToScroll);

	if (--x < -lenght * 5) //the number (5) controls how many columns the text will scroll for. The longer the text, the more columns scrolled
	{
		x = matrix.width();
	}

	matrix.show();
	delay(scrollSpeed);
}

void MatrixClock::showText(const String& textToShow)
{

	int cursor = matrix.width() / (textToShow.length() + 1);
	matrix.fillScreen(0);
	matrix.setCursor(cursor, 7);
	matrix.print(textToShow);
	matrix.show();
	delay(50);
}
#pragma endregion

#pragma region RTC Functionality


void MatrixClock::showDate()
{
	String date = rtc.getDateStr();
	scrollText(date);
}

void MatrixClock::showFullDate()
{
	String date = rtc.getDOWStr();
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
		
	scrollText(date, 85);
}

void MatrixClock::showTime()
{

	String time = "";

	switch (rtc.getTime().sec % 2)
		{
			
		case 0:
			time = (String)rtc.getTime().hour;
			time += " ";
			if (rtc.getTime().min < 10)
				time += "0";
			
			time += rtc.getTime().min;

			if (time.endsWith("00") && !buzzedAtFullHour)
			{
				buzzer.buzz(80, 150);
				buzzedAtFullHour = true;
			}

			else if (time.endsWith("01") && buzzedAtFullHour)
			{
				buzzedAtFullHour = false;
			}

			
			showText(time);
			break;
			
		case 1:
			time = (String)rtc.getTime().hour;
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
	String temp = "";

	if (joystick.getMovementX() == 0)
	{
		temp = (String)((int)rtc.getTemp());
		temp += "' C";
		showText(temp);
	}

	else
	{
		temp = (String)((int)(rtc.getTemp() * 1.8 + 32));
		temp += "' F";
		showText(temp);
	}

}

void MatrixClock::showTimeAndDate()
{
	unsigned long currentTime = millis();
	bool modeChanged = false;

	while ((millis() - currentTime) < 45000 && !modeChanged) //show the time for 45000ms (45s)
	{
		showTime();
		modeChanged = joystick.isPressed();
	
	}

	currentTime = millis();
	x = matrix.width();

	while ((millis() - currentTime) < 10000 && !modeChanged) //it takes ~10000ms (10s) to scroll the entire FullDate()
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
			matrix.setTextColor(BLUE);
			showText("BLU");
			break;

		case 1:
			delay(50);
			matrix.setTextColor(GREEN);
			showText("GRN");
			break;

		case 2:
			delay(50);
			matrix.setTextColor(RED);
			showText("RED");
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
			showText("CYAN");
			break;

		case 6:
			delay(50);
			matrix.setTextColor(MAGENTA);
			showText("MGT");
			break;
		default:
			break;

		}

		if (joystick.isPressed())
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

void MatrixClock::changeTime()
{
	uint8_t hourBuffer = 0;
	uint8_t minuteBuffer = 0;
	String textToDisplay = "";

	bool isChoosing = true;
	bool isEditing = true;

	while (isChoosing)
	{
		scrollText("Change time. Sure? UP - YES, DOWN - NO", 80);
		switch (joystick.getMovementY())
		{
		case -1:
			isChoosing = false;
			while (isEditing)
			{
				textToDisplay = " ";
				minuteBuffer = (minuteBuffer + joystick.getMovementX());
				delay(25);
				hourBuffer = (hourBuffer - joystick.getMovementY()) ;
				delay(25);

				hourBuffer = constrain(hourBuffer, 0, 23);
				minuteBuffer = constrain(minuteBuffer, 0, 59);

				textToDisplay += hourBuffer;
				textToDisplay += ":";
				textToDisplay += minuteBuffer;

				showText(textToDisplay);

				delay(25);

				if (joystick.isPressed())
				{
					isEditing = false;
					rtc.setTime(hourBuffer, minuteBuffer, 0);
					modeCounter++;
					delay(200);
				}
			}
			break;
		case 1:
			showText("abort");
			delay(500);
			isChoosing = false;
			modeCounter++;
			break;

		case 0:
			break;
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
		//clear back buffer
		clearDisplayBuffer();

		//timing and input
		int8_t playerMovement = joystick.getMovementY();
		int8_t aiMovement = (random(0, 1023) > 512 ? -1 : 1);
		delay(100);

		//game logic
		movePaddle(paddle1, playerMovement);
		movePaddle(paddle2, aiMovement);

		moveBall(ball1);
		moveBall(ball2);


		//check whether the ball is getting closer to the paddle, if so enter the function.
		if (ball1.x < 3 || ball1.x > 20)
		{
			didPaddleHitBall(paddle1, ball1);
			didPaddleHitBall(paddle2, ball1);
		}

		if (ball2.x < 3 || ball2.x > 20)
		{
			didPaddleHitBall(paddle1, ball2);
			didPaddleHitBall(paddle2, ball2);
		}
		
		//display to player, flush back buffer
		drawDisplayBuffer();

	

		//exit game logic
		if (joystick.isPressed())
		{
			String score;
			score += paddle2.score;
			score += "-";
			score += paddle1.score;
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
	if (paddle.paddleBlocks[0] + direction < 0 || paddle.paddleBlocks[1] + direction > 7)
	{
	
		displayBuffer[paddle.startX][paddle.paddleBlocks[0]] = paddle.color;
		displayBuffer[paddle.startX][paddle.paddleBlocks[1]] = paddle.color;
	}
	else
	{
		paddle.paddleBlocks[0] += direction;
		paddle.paddleBlocks[1] += direction;

		displayBuffer[paddle.startX][paddle.paddleBlocks[0]] = paddle.color;
		displayBuffer[paddle.startX][paddle.paddleBlocks[1]] = paddle.color;
	}
}

void MatrixClock::moveBall(ball& ball)
{

	ball.x += ball.momentumX;

	//bounce the ball off top and bottom edges of the screen.
	if (ball.y + ball.momentumY > 7 || ball.y + ball.momentumY < 0)
	{
		ball.momentumY *= -1;
		buzzer.buzz();
	}

	ball.y += ball.momentumY;

	displayBuffer[ball.x][ball.y] = ball.color;

}

void MatrixClock::resetBall(ball& ball)
{
	ball.x = random(8, 15);
	ball.y = random(0, 7);
}


bool MatrixClock::didPaddleHitBall(paddle& paddle, ball& ball)
{
	//checks if the ball hits one of the parts of the passed in paddle paddle
	if ((ball.y == paddle.paddleBlocks[0] && ball.x == paddle.startX - (ball.momentumX) ||
		(ball.y == paddle.paddleBlocks[1] && ball.x == paddle.startX - (ball.momentumX))))
	{
		ball.momentumX *= -1;
		buzzer.buzz(35);
		return true;
	}

	//check to see if the ball hits the passed in paddle diagonally from top right
	else if ((ball.y == (paddle.paddleBlocks[0] - 1) && ball.x == paddle.startX - (ball.momentumX)
		&& (ball.y != paddle.paddleBlocks[0] && ball.momentumY > 0)))
	{
	
		ball.momentumX *= -1;
		ball.momentumY *= -1;
		buzzer.buzz(35);
		return true;
	}

	//check to see if the ball hits the passed in paddle diagonally from bottom right
	else if ((ball.y == (paddle.paddleBlocks[1] + 1) && ball.x == paddle.startX - (ball.momentumX) && 
		(ball.y != paddle.paddleBlocks[1] && ball.momentumY < 0)))
	{
		ball.momentumX *= -1;
		ball.momentumY *= -1;
		buzzer.buzz(35);
		return true;
	}

	else if (ball.x == paddle.startX)
	{
		paddle.score++;
		buzzer.buzz(100);
		resetBall(ball);
		delay(100);
		return false;
	}

}
#pragma endregion
