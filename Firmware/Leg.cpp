#include "Leg.h"

Leg::Leg(Point3D rootPoint, Joint *newCoxa, Joint *newTrochanter, Joint *newPatella)
{
	root = rootPoint;
	coxa = newCoxa;
	trochanter = newTrochanter;
	patella = newPatella;
}