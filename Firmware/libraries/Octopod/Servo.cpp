#include "Servo.h"

Servo::Servo(Adafruit_PWMServoDriver *newDriver, uint8_t newNum, uint16_t newRange, uint16_t newPulseWidthMin, uint16_t newPulseWidthMax, uint8_t newInverted)
{
  Serial.println("Servo Constructor");
  driver = newDriver;
  servoNumber = newNum;
  range = newRange;
  pulseWidthMin = newPulseWidthMin;
  pulseWidthMax = newPulseWidthMax;
  pulseWidthRange = pulseWidthMax - pulseWidthMin;
  inverted = newInverted;
}


/*************************************************************************/
/******************************POSITION DATA******************************/
/*************************************************************************/
void Servo::setRange(uint16_t newRange)
{
  range = newRange;
}

uint16_t Servo::getRange()
{
  return range;
}

void Servo::setAngle(uint16_t newAngle)
{
  if (inverted)
  {
    newAngle = range - newAngle;
  }
  Serial.println("Set Angle if");
  Serial.println(newAngle);
  if (newAngle >= 0 && newAngle <= range)
  {
    angle = newAngle;

    float percentage = ((float)angle) / ((float)range);
    Serial.println("Set Angle Called");
    Serial.println(percentage);
    Serial.println(pulseWidthMin);
    Serial.println(pulseWidthRange);
    Serial.println(pulseWidthMin + (pulseWidthRange * percentage));
    driver->setPWM(servoNumber, 0, pulseWidthMin + ((float)pulseWidthRange * percentage));
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

void Servo::setDriver(Adafruit_PWMServoDriver *newDriver)
{
  driver = newDriver;
}

Adafruit_PWMServoDriver	*Servo::getDriver()
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
  Serial.println("Sweep Called");
  for (uint8_t i = 0; i < numIterations; i++)
  {
    moveToLimitLo();
    delay(delayTime);
    moveToLimitHi();
    delay(delayTime);
  }
}

