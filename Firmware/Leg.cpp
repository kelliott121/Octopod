#include "Leg.h"

Leg::Leg(Point3D *rootPoint, uint16_t newCoxaLength, newTrochanterLength, newPatellaLength, Joint *newCoxa, Joint *newTrochanter, Joint *newPatella)
{
	root = rootPoint;
	coxaLength = newCoxaLength;
	trochanterLength = newTrochanterLength;
	patellaLength = newPatellaLength;
	coxa = newCoxa;
	trochanter = newTrochanter;
	patella = newPatella;
}

/*************************************************************************/
/****************************MOTION FUNCTIONS*****************************/
/*************************************************************************/

	void Leg::home()
{
	coxa->home();
	trochanter->home();
	patella->home();
}

void Leg::home(uint16_t speed)
{
	coxa->home(speed);
	trochanter->home(speed);
	patella->home(speed);
}

void moveCartesian(Point3D *target)
{
	float coxaAngle = atan((target->y - root->y) / (target->x - root->x));
	coxa->setAngle((int16_t)coxaAngle);
	
	float trochanterAngle, patellaAngle;
	float alpha1, alpha2;
	float lengthRZ;
	float lengthXY = sqrt(pow(target->x - root->x, 2) + pow(target->y - root->y, 2));
	lengthRZ = sqrt(pow(root->z - target->z, 2) + pow(lengthXY - coxaLength));
	
	alpha1 = acos((root->z - target->z) / lengthRZ);
	alpha2 = acos((pow(patellaLength, 2) - pow(trochanterLength, 2) - pow(lengthRZ, 2)) / (-2 * trochanterLength * lengthRZ));
	
	trochanterAngle = alpha1 + alpha2;
	trochanter->setAngle((int16_t)trochanterAngle);
	
	patellaAngle = acos((pow(lengthRZ, 2) - pow(lengthPatella, 2) - pow(lengthTrochanter, 2)) / (-2 * patellaLength * lengthRZ));
	patella->setAngle((int16_t)patellaAngle);
}

void moveCartesian(Point3D *target, uint16_t speed)
{
	
}

void moveToCartesian(Point3D *target)
{
	
}

void moveToCartesian(Point3D *target, uint16_t speed)
{
	
}

void moveAngular(int16_t coxaAngle, int16_t trochanterAngle, int16_t patellaAngle)
{
	
}

void moveAngular(int16_t coxaAngle, int16_t trochanterAngle, int16_t patellaAngle)
{
	
}

void moveToAngular(int16_t coxaAngle, int16_t trochanterAngle, int16_t patellaAngle)
{
	
}

void moveToAngular(int16_t coxaAngle, int16_t trochanterAngle, int16_t patellaAngle)
{
	
}
