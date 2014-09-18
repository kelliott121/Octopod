#include "Octopod.h"

Octopod()
{
	int16_t hipX = X_HIP_SPACING / 2;
	int16_t hipY = Y_HIP_SPACING * 1.5;
	int16_t angleOffset = HIP_ANGLE_SPACING * 1.5;
	
	rightDriver = new Adafruit_PWMServoDriver(0x40);
	leftDriver = new Adafruit_PWMServoDriver(0x41);
	
	Joint * tempServos[3];
	
	for (int i = 0; i < NUM_LEGS / 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			tempServos[j] = new Servo(	rightDriver,
										(i * 3) + j,
										SERVO_RANGE,
										SERVO_MIN,
										SERVO_MAX,
										0;
		}
		legs[i] = new Leg(	new Point3D(hipX, hipY, Z_HIP_HEIGHT)
							COXA_LENGTH, TROCHANTER_LENGTH, PATELLA_LENGTH,
							new Joint(tempServos[0]),
							new Joint(tempServos[1]),
							new Joint(tempServos[2]));
		
		hipY -= Y_HIP_SPACING;
		angleOffset -= HIP_ANGLE_SPACING;
	}
	
	for (int i = NUM_LEGS / 2; i < NUM_LEGS; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			tempServos[j] = new Servo(	rightDriver,
										(i * 3) + j,
										SERVO_RANGE,
										SERVO_MIN,
										SERVO_MAX,
										1;
		}
		legs[i] = new Leg(	new Point3D(hipX, hipY, Z_HIP_HEIGHT)
							COXA_LENGTH, TROCHANTER_LENGTH, PATELLA_LENGTH,
							new Joint(tempServos[0]),
							new Joint(tempServos[1]),
							new Joint(tempServos[2]));
		
		hipY += Y_HIP_SPACING;
		angleOffset += HIP_ANGLE_SPACING;
	}
}

~Octopod()
{
	
}

/*************************************************************************/
/****************************MOTION FUNCTIONS*****************************/
/*************************************************************************/
void home()
{
	
}

void step(uint8_t legNumbe, int16_t distance)
{
	
}

/*************************************************************************/
/**************************TRAJECTORY FUNCTIONS***************************/
/*************************************************************************/
void move(int16_t distance)
{
	
}

void move(uint16_t speed)
{
	
}

void rotate(int16_t angle)
{
	
}

void roll(int16_t pitchAngle, int16_t directionAngle)
{
	
}
