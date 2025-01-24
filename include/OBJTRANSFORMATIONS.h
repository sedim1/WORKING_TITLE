#ifndef OBJTRANSFORMATIONS
#define OBJTRANSFORMATIONS

#include "radians.h"
#include <cglm/cglm.h>

typedef struct
{
	vec3 position; //Current position
	vec3 size; //Size
	vec3 pivot; //Point that will take accoount for transformations
	float pitch;//ANGLE X
	float yaw;//ANGLE Y
	float roll;//ANGLE Z
	mat4 model;
}SPATIAL_ATTRIBUTES;

SPATIAL_ATTRIBUTES spatialAttributes();//Constructor
void updateModelMatrix(SPATIAL_ATTRIBUTES* A);

#endif
