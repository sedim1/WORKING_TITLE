#ifndef MATRIX_H
#define MATRIX_H

#include"vector.h"
#include<math.h>

#define M_PI 3.14159265358979323846

typedef float Matrix4x4[4][4];

//Matrix Transformations and Operations;
void initializeMatrix(Matrix4x4 matrix);
void scale(Matrix4x4 matrix, VECTOR4D S);
void scalarScale(Matrix4x4 matrix,float S);
void translate(Matrix4x4 matrix, VECTOR4D T);
void rotateX(Matrix4x4 matrix,float degrees);
void rotateY(Matrix4x4 matrix,float degrees);
void rotateZ(Matrix4x4 matrix,float degrees);
void matrixMultiplication(Matrix4x4 R,Matrix4x4 A,Matrix4x4 B);

#endif
