#include "Servo.h"

class Joint
{
	// POSITION DATA
	int16_t homeOffset;
	int16_t angularOffset;
	int16_t softLimitLo, softLimitHi;
	int16_t angle;
	
	Servo *servo;
	
  public:
	// Constructor
    Joint(Servo *newServo, int16_t offset);
	~Joint();
	
	/*************************************************************************/
	/******************************POSITION DATA******************************/
	/*************************************************************************/
	void	setHome(int16_t newHome);
	int16_t	getHome();
	
	void	setOffset(int16_t newOffset);
	int16_t	getOffset();
	
	void	setAngle(int16_t newAngle);
	int16_t	getAngle();
	
	void	setSoftLimits(int16_t newLo, int16_t newHi);
	int16_t	getSoftLimitLo();
	int16_t	getSoftLimitHi();
	
	/*************************************************************************/
	/****************************MOTION FUNCTIONS*****************************/
	/*************************************************************************/
	void home();
	void home(uint16_t speed);
	void move(int16_t distance);
	void move(int16_t distance, uint16_t speed);
	void moveTo(int16_t destination);
	void moveTo(int16_t destination, uint16_t speed);
};