#include "Joint.h"

Joint::Joint(Servo *newServo, int16_t offset)
{
	servo = newServo;
	angularOffset = offset;
	
	int16_t halfRange = servo->getRange() / 2;
	// Default home is center of travel on the servo
	homeOffset = halfRange;
	softLimitLo = -halfRange;
	softLimitHi = halfRange;
}

Joint::~Joint()
{
	delete servo;
}

	
/*************************************************************************/
/******************************POSITION DATA******************************/
/*************************************************************************/
void Joint::setHome(int16_t newHome)
{
	homeOffset = newHome;
}

int16_t Joint::getHome()
{
	return homeOffset;
}

void setOffset(int16_t newOffset)
{
	angularOffset = newOffset;
}

int16_t getOffset()
{
	return angularOffset;
}

void Joint::setAngle(int16_t newAngle)
{
	angle = newAngle;
	
	servo->setAngle(angle + homeOffset);
}

int16_t Joint::getAngle()
{
	return angle;
}

void Joint::setSoftLimits(int16_t newLo, int16_t newHi)
{
	softLimitLo = newLo;
	softLimitHi = newHi;
}

int16_t Joint::getSoftLimitLo()
{
	return softLimitLo;
}

int16_t Joint::getSoftLimitHi()
{
	return softLimitHi;
}


/*************************************************************************/
/****************************MOTION FUNCTIONS*****************************/
/*************************************************************************/
void Joint::home()
{
	setAngle(0);
}

void Joint::home(uint16_t speed)
{
	moveTo(0, speed);
}

void Joint::move(int16_t distance)
{
	setAngle(angle + distance);
}

void Joint::move(int16_t distance, uint16_t speed)
{
	uint16_t tstep = 1000 / speed;
	
	if (distance > 0)
	{
		for (int16_t i = 0; i < distance; i++)
		{
			setAngle(angle + 1);
			delay(tstep);
		}
	}
	else if (distance < 0)
	{
		for (int16_t i = 0; i > distance; i--)
		{
			setAngle(angle - 1);
			delay(tstep);
		}
	}
}

void Joint::moveTo(int16_t destination)
{
	move(destination - angle);
}

void Joint::moveTo(int16_t destination, uint16_t speed)
{
	move(destination - angle, speed);
}
