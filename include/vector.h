#ifndef VECTOR_H
#define VECTOR_H

#include<math.h>

typedef struct
{
	float x;
	float y;
	float z;
	float w; //VALUE RANGE: 0 - 1
}VECTOR4D;

//4D VECTOR CREATION AND OPERATIONS
VECTOR4D vector4D(float nx,float ny,float nz, float nw);
VECTOR4D sumVector(VECTOR4D A,VECTOR4D B);
VECTOR4D substractVector(VECTOR4D A, VECTOR4D B);
VECTOR4D scalar(VECTOR4D A,float C);
float lenght(VECTOR4D A);
VECTOR4D normalized(VECTOR4D A);
VECTOR4D crossProduct(VECTOR4D A,VECTOR4D B);

#endif
