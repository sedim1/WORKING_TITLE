#ifndef VECTOR_H
#define VECTOR_H

#include<math.h>

typedef struct
{
	float x;
	float y;
	float z;
}VECTOR3D;

//4D VECTOR CREATION AND OPERATIONS
VECTOR3D vector3D(float nx,float ny,float nz);
VECTOR3D sumVector(VECTOR3D *A,VECTOR3D *B);
VECTOR3D substractVector(VECTOR3D *A, VECTOR3D *B);
VECTOR3D scalar(VECTOR3D *A,float C);
float lenght(VECTOR3D *A);
VECTOR3D normalized(VECTOR3D *A);
VECTOR3D crossProduct(VECTOR3D *A,VECTOR3D *B);
float dotProduct(VECTOR3D *A,VECTOR3D *B);

#endif
