#include "Leg.h"

Leg::Leg(Point3D *rootPoint, uint16_t newCoxaLength, uint16_t newTrochanterLength, uint16_t newPatellaLength, Joint *newCoxa, Joint *newTrochanter, Joint *newPatella)
{
	root = rootPoint;
	coxaLength = newCoxaLength;
	trochanterLength = newTrochanterLength;
	patellaLength = newPatellaLength;
	coxa = newCoxa;
	trochanter = newTrochanter;
	patella = newPatella;
}

Leg::~Leg()
{
	delete root;
	delete coxa;
	delete trochanter;
	delete patella;
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

void Leg::moveCartesian(Point3D *target)
{
	Point3D *absTarget = new Point3D(	root->x + target->x,
										root->y + target->y,
										root->z + target->z);
	moveToCartesian(absTarget);
	delete absTarget;
}

void Leg::moveToCartesian(Point3D *target)
{
	float coxaAngle = atan((target->y - root->y) / (target->x - root->x));
	
	float trochanterAngle, patellaAngle;
	float alpha1, alpha2;
	float lengthRZ;
	float lengthXY = sqrt(pow(target->x - root->x, 2) + pow(target->y - root->y, 2));
	lengthRZ = sqrt(pow(root->z - target->z, 2) + pow(lengthXY - coxaLength, 2));
	
	alpha1 = acos((root->z - target->z) / lengthRZ);
	alpha2 = acos((pow(patellaLength, 2) - pow(trochanterLength, 2) - pow(lengthRZ, 2)) / (-2 * trochanterLength * lengthRZ));
	
	trochanterAngle = alpha1 + alpha2;
	
	patellaAngle = acos((pow(lengthRZ, 2) - pow(patellaLength, 2) - pow(trochanterLength, 2)) / (-2 * patellaLength * lengthRZ));
	
	moveToAngular((int16_t)coxaAngle, (int16_t)trochanterAngle, (int16_t)patellaAngle);
	point->x = target->x;
	point->y = target->y;
	point->z = target->z;
}

void Leg::moveAngular(int16_t coxaAngle, int16_t trochanterAngle, int16_t patellaAngle)
{
	coxa->move(coxaAngle);
	trochanter->move(trochanterAngle);
	patella->move(patellaAngle);
}

void Leg::moveToAngular(int16_t coxaAngle, int16_t trochanterAngle, int16_t patellaAngle)
{
	coxa->moveTo(coxaAngle);
	trochanter->moveTo(trochanterAngle);
	patella->moveTo(patellaAngle);
}

void Leg::arc(Point3D *target, int16_t radius, uint16_t speed)
{
	float startX, startY, startZ;
	float endX, endY, endZ;
	float centerX, centerY, centerZ;
	float tempX, tempY, tempZ;
	float coeffStart, coeffEnd;
	Point3D *tempPoint = new Point3D(0, 0, 0);
	
	startX = point->x;
	startY = point->y;
	startZ = point->z;
	endX = point->x;
	endY = point->y;
	endZ = point->z;
	
	centerX = (startX + endX) / 2.0;
	centerY = (startY + endY) / 2.0;
	centerZ = (startZ + endZ) / 2.0;
	
	float traversedAngle = 180;
	float incrementAngle = 30;
	
	for (float angle = incrementAngle; angle < traversedAngle; angle++)
	{
		coeffStart = sin(traversedAngle - angle);
		coeffEnd = sin(angle);
		tempX = centerX + (((coeffStart * startX) + (coeffEnd * endX)) / sin(angle));
		tempY = centerY + (((coeffStart * startY) + (coeffEnd * endY)) / sin(angle));
		tempZ = centerZ + (((coeffStart * startZ) + (coeffEnd * endZ)) / sin(angle));
		
		tempPoint->x = tempX;
		tempPoint->y = tempY;
		tempPoint->z = tempZ;
		
		moveCartesian(tempPoint);
	}
	
	moveCartesian(target);
	
	delete tempPoint;
}

void Leg::linear(Point3D *target, uint16_t speed)
{
	float startX, startY, startZ;
	float endX, endY, endZ;
	float diffX, diffY, diffZ;
	float percentage;
	Point3D *tempPoint = new Point3D(0, 0, 0);
	
	startX = point->x;
	startY = point->y;
	startZ = point->z;
	endX = point->x;
	endY = point->y;
	endZ = point->z;
	
	diffX = startX - endX;
	diffY = startY - endY;
	diffZ = startZ - endZ;
	
	for (percentage = 10; percentage < 100; percentage+=10)
	{
		tempPoint->x = diffX * percentage;
		tempPoint->y = diffY * percentage;
		tempPoint->z = diffZ * percentage;
		
		moveCartesian(target);
	}
	
	moveCartesian(target);
	
	delete tempPoint;
}
