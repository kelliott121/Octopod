#include "Leg.h"
#include <Adafruit_PWMServoDriver.h>
#include "Point3D.h"

#define NUM_LEGS			8

#define X_HIP_SPACING		20
#define Y_HIP_SPACING		20
#define Z_HIP_HEIGHT		20
#define HIP_ANGLE_SPACING	30

#define COXA_LENGTH			10
#define TROCHANTER_LENGTH	20
#define PATELLA_LENGTH		30

#define SERVO_MIN			150
#define SERVO_MAX			600

#define SERVO_RANGE			180

class Octopod
{
	Leg * legs[NUM_LEGS];
	Adafruit_PWMServoDriver *rightDriver;
	Adafruit_PWMServoDriver *leftDriver;
  public:
	
	// Constructor
    Octopod();
	~Octopod();
	
	/*************************************************************************/
	/****************************MOTION FUNCTIONS*****************************/
	/*************************************************************************/
	void home();
	void step(uint8_t legNumbe, int16_t distance);
	
	/*************************************************************************/
	/**************************TRAJECTORY FUNCTIONS***************************/
	/*************************************************************************/
	void move(int16_t distance);
	void move(uint16_t speed);
	void rotate(int16_t angle);
	void roll(int16_t pitchAngle, int16_t directionAngle);	
};
