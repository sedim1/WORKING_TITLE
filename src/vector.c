#include"vector.h"

VECTOR4D vector4D(float nx,float ny,float nz,float nw)
{
	VECTOR4D new;
	new.x = nx;
	new.y = ny;
	new.z = nz;
	new.w = nw;
	return new;
}

VECTOR4D sumVector(VECTOR4D A,VECTOR4D B)
{
	VECTOR4D new;
	new.x = A.x + B.x;
	new.x = A.y + B.y;
	new.x = A.z + B.z;
	return new;
}

VECTOR4D substractVector(VECTOR4D A, VECTOR4D B)
{
	VECTOR4D new;
	new.x = A.x - B.x;
	new.x = A.y - B.y;
	new.x = A.z - B.z;
	return new;
}

VECTOR4D scalar(VECTOR4D A,float C)
{
	VECTOR4D new;
	new.x = C * A.x;
	new.x = C * A.y;
	new.x = C * A.z;
	return new;
}

float lenght(VECTOR4D A)
{
	return sqrt(pow(A.x,2)+pow(A.y,2)+pow(A.z,2));
}

VECTOR4D normalized(VECTOR4D A)
{
	VECTOR4D new;
	float len = lenght(A);
	new.x = A.x/len;
	new.x = A.y/len;
	new.x = A.z/len;
	return new;
}

VECTOR4D crossProduct(VECTOR4D A,VECTOR4D B)
{
	VECTOR4D new;
	new.x = (A.y * B.z) - (A.z * B.y);
	new.y = (A.z * B.x) - (A.x * B.z);
	new.z = (A.x * B.y) - (A.y * B.x);
	return new;
}
