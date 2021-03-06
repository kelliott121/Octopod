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
    Leg(Point3D *rootPoint, uint16_t newCoxaLength, uint16_t newTrochanterLength, uint16_t newPatellaLength, Joint *newCoxa, Joint *newTrochanter, Joint *newPatella);
	~Leg();
	
	/*************************************************************************/
	/****************************MOTION FUNCTIONS*****************************/
	/*************************************************************************/
	void home();
	void home(uint16_t speed);
	void moveCartesian(Point3D *target);
	void moveToCartesian(Point3D *target);
	void moveAngular(int16_t coxaAngle, int16_t trochanterAngle, int16_t patellaAngle);
	void moveToAngular(int16_t coxaAngle, int16_t trochanterAngle, int16_t patellaAngle);
	
	/*************************************************************************/
	/**************************TRAJECTORY FUNCTIONS***************************/
	/*************************************************************************/
	void arc(Point3D *target, int16_t radius, uint16_t speed);
	void linear(Point3D *target, uint16_t speed);
};
