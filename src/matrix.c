#include "matrix.h"

void initializeMatrix(Matrix4x4 matrix)
{
	for(int i = 0;i < 4;i++)
	{
		for(int j = 0;j < 4;j++)
		{
			if(i==j)
				matrix[i][j] = 1;
			else
				matrix[i][j] = 0;
		}
	}
}

void scale(Matrix4x4 matrix, VECTOR3D *S)
{
	matrix[0][0] = S->x;
	matrix[1][1] = S->y;
	matrix[2][2] = S->z;
}

void scalarScale(Matrix4x4 matrix, float S)
{
	matrix[0][0] = S;
	matrix[1][1] = S;
	matrix[2][2] = S;
}

void translate(Matrix4x4 matrix, VECTOR3D *T)
{
	matrix[3][0] = T->x;
	matrix[3][1] = T->y;
	matrix[3][2] = T->z;
}

void rotateX(Matrix4x4 matrix, float degrees)
{
	float radians = (degrees * M_PI) / 180.0f;
	float cosine = cos(radians);
	float sine = sin(radians);
	matrix[1][1] = cosine;
	matrix[1][2] = -sine;
	matrix[2][1] = sine;
	matrix[2][2] = cosine;
}

void rotateY(Matrix4x4 matrix, float degrees)
{
	float radians = (degrees * M_PI) / 180.0f;
	float cosine = cos(radians);
	float sine = sin(radians);
	matrix[0][0] = cosine;
	matrix[0][2] = sine;
	matrix[2][0] = -sine;
	matrix[2][2] = cosine;
}

void rotateZ(Matrix4x4 matrix, float degrees)
{
	float radians = (degrees * M_PI) / 180.0f;
	float cosine = cos(radians);
	float sine = sin(radians);
	matrix[0][0] = cosine;
	matrix[0][1] = -sine;
	matrix[1][0] = sine;
	matrix[1][1] = cosine;
}

void matrixMultiplication(Matrix4x4 R,Matrix4x4 A,Matrix4x4 B)
{
	for(int i = 0;i < 4;i++)
		for(int j = 0;j < 4;j++)
			for(int k = 0;k < 4;k++)
				R[i][j] += (A[i][k] * B[k][j]); 
}

void printMatrix(Matrix4x4 matrix)
{
	for(int i = 0;i < 4;i++)
	{
		for(int j = 0; j < 4;j++)
			printf("%f ",matrix[i][j]);

		printf("\n");
	}
}
