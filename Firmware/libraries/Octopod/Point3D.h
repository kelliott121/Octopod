#ifndef POINT3D_H
#define POINT3D_H

#include <stdint.h>

class Point3D
{
  public:
	uint16_t x,y,z;
	
	// Constructor
    Point3D(uint16_t newX, uint16_t newY, uint16_t newZ);
	
};
#endif
