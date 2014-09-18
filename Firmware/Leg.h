#include "Joint.h"
#include "Point3D.h"

class Leg
{
	Point3D *root;
  public:
	Joint *coxa;
	Joint *trochanter;
	Joint *patella;
	
	uint16_t coxaLength, trochanterLength, patellaLength;
	
	Point3D *point;
	
	// Constructor
    Leg(Point3D *rootPoint, uint16_t newCoxaLength, newTrochanterLength, newPatellaLength, Joint *newCoxa, Joint *newTrochanter, Joint *newPatella);
	
	/*************************************************************************/
	/****************************MOTION FUNCTIONS*****************************/
	/*************************************************************************/
	void home();
	void home(uint16_t speed);
	void moveCartesian(int16_t X, int16_t Y, int16_t Z);
	void moveToCartesian(int16_t X, int16_t Y, int16_t Z);
	void moveAngular(int16_t coxaAngle, int16_t trochanterAngle, int16_t patellaAngle);
	void moveToAngular(int16_t coxaAngle, int16_t trochanterAngle, int16_t patellaAngle);
};
