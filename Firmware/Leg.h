#include "Joint.h"
#include "Point3D.h"

class Leg
{
	Point3D root;
  public:
	Joint *coxa;
	Joint *trochanter;
	Joint *patella;
	
	// Constructor
    Leg(Point3D rootPoint, Joint *newCoxa, Joint *newTrochanter, Joint *newPatella);
	
	/*************************************************************************/
	/****************************MOTION FUNCTIONS*****************************/
	/*************************************************************************/
	
};