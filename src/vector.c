#include"vector.h"

VECTOR3D vector3D(float nx,float ny,float nz)
{
	VECTOR3D new;
	new.x = nx;
	new.y = ny;
	new.z = nz;
	return new;
}

VECTOR3D sumVector(VECTOR3D *A,VECTOR3D *B)
{
	VECTOR3D new;
	new.x = A->x + B->x;
	new.y = A->y + B->y;
	new.z = A->z + B->z;
	return new;
}

VECTOR3D substractVector(VECTOR3D *A, VECTOR3D *B)
{
	VECTOR3D new;
	new.x = A->x - B->x;
	new.y = A->y - B->y;
	new.z = A->z - B->z;
	return new;
}

VECTOR3D scalar(VECTOR3D *A,float C)
{
	VECTOR3D new;
	new.x = C * A->x;
	new.y = C * A->y;
	new.z = C * A->z;
	return new;
}

float lenght(VECTOR3D *A)
{
	return sqrt(A->x*A->x+A->y*A->y+A->z*A->z);
}

VECTOR3D normalized(VECTOR3D *A)
{
	VECTOR3D new;
	float len = lenght(A);
	new.x = A->x/len;
	new.y = A->y/len;
	new.z = A->z/len;
	return new;
}

VECTOR3D crossProduct(VECTOR3D *A,VECTOR3D *B)
{
	VECTOR3D new;
	new.x = (A->y * B->z) - (A->z * B->y);
	new.y = (A->z * B->x) - (A->x * B->z);
	new.z = (A->x * B->y) - (A->y * B->x);
	return new;
}

float dotProduct(VECTOR3D *A,VECTOR3D *B)
{
	return ( (A->x * B->x )+( A->y * B->y )+ ( A->z * B->z ) );
}
