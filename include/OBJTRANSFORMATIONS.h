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
}SPATIAL_ATTRIBUTES;

SPATIAL_ATTRIBUTES spatialAttributes();//Constructor
void manipulateAttributes(SPATIAL_ATTRIBUTES* A, mat4 modelMatrix);

#endif
