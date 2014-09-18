#include "Servo.h"

Servo::Servo(Adafruit_PWMServoDriver newDriver, uint16_t newRange, uint16_t newPulseWidthMin, uint16_t newPulseWidthMax, uint8_t newInverted)
{
	driver = newDriver;
	range = newRange;
	pulseWidthMin = newPulseWidthMin;
	pulseWidthMax = newPulseWidthMax;
	inverted = newInverted;
}


/*************************************************************************/
/******************************POSITION DATA******************************/
/*************************************************************************/
void Servo::setRange(uint16_t newRange)
{
	range = newRange;
}

uint16_T Servo::getRange()
{
	return range;
}

void Servo::setAngle(uint16_t newAngle)
{
	if (inverted)
	{
		newAngle = range - newAngle;
	}
	
	if (angle >= 0 && angle <= range)
	{
		angle = newAngle;

		float percentage = ((float)angle) / ((float)range);
		driver.setPWM(servo, 0, pulseWidthMin + (pulseWidthRange * percentage));
	}
}

uint16_t Servo::getAngle()
{
	return angle;
}

void Servo::setPulseWidths(uint16_t newMin, uint16_t newMax)
{
	pulseWidthMin = newMin;
	pulseWidthMax = newMax;
	pulseWidthRange = pulseWidthMax - pulseWidthMin;
}

uint16_t Servo::getPulseWidthMin()
{
	return pulseWidthMin;
}

uint16_t Servo::getPulseWidthMax()
{
	return pulseWidthMax;
}

void Servo::setInverted(uint8_t newInverted)
{
	inverted = newInverted;
}

uint8_t Servo::getInverted()
{
	return inverted;
}


/*************************************************************************/
/*******************************DRIVER DATA*******************************/
/*************************************************************************/

void Servo::setDriver(Adafruit_PWMServoDriver newDriver)
{
	driver = newDriver;
}

Adafruit_PWMServoDriver	Servo::getDriver()
{
	return driver;
}

void Servo::setServoNumber(uint8_t newNum)
{
	servoNumber = newNum;
}

uint8_t Servo::getServoNumber()
{
	return servoNumber;
}


/*************************************************************************/
/****************************MOTION FUNCTIONS*****************************/
/*************************************************************************/
void Servo::moveToLimitHi()
{
	setAngle(range);
}

void Servo::moveToLimitLo()
{
	setAngle(0);
}

void Servo::center()
{
	setAngle(range / 2);
}

void Servo::sweep(uint8_t numIterations, uint16_t delayTime)
{
	for (uint8_t i = 0; i < numIterations; i++)
	{
		moveToLimitLo();
		delay(delayTime);
		moveToLimitHi();
		delay(delayTime);
	}
}
