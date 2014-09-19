#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#ifdef __cplusplus
extern "C" {
#endif

class Servo
{
	// POSITION DATA
    uint16_t range;
	uint16_t angle;
	
	uint16_t pulseWidthMin, pulseWidthMax;
	uint16_t pulseWidthRange;
	
	uint8_t inverted;
	
	// DRIVER DATA
	Adafruit_PWMServoDriver *driver;
	uint8_t servoNumber;
	
  public:
	// Constructor
    Servo(Adafruit_PWMServoDriver *newDriver, uint8_t newNum, uint16_t newRange, uint16_t pulseWidthMin, uint16_t pulseWidthMax, uint8_t newInverted);
	
	/*************************************************************************/
	/******************************POSITION DATA******************************/
	/*************************************************************************/
	void		setRange(uint16_t newRange);
	uint16_t	getRange();
	
	void		setAngle(uint16_t newAngle);
	uint16_t	getAngle();
	
	void		setPulseWidths(uint16_t newMin, uint16_t newMax);
	uint16_t	getPulseWidthMin();
	uint16_t	getPulseWidthMax();
	
	void		setInverted(uint8_t newInverted);
	uint8_t		getInverted();
	
	/*************************************************************************/
	/*******************************DRIVER DATA*******************************/
	/*************************************************************************/
	
	void		setDriver(Adafruit_PWMServoDriver *newDriver);
	Adafruit_PWMServoDriver	*getDriver();
	
	void		setServoNumber(uint8_t newNum);
	uint8_t		getServoNumber();
	
	/*************************************************************************/
	/****************************MOTION FUNCTIONS*****************************/
	/*************************************************************************/
	void moveToLimitHi();
	void moveToLimitLo();
	void center();
	void sweep(uint8_t numIterations, uint16_t delayTime);
};

#ifdef __cplusplus
}
#endif
