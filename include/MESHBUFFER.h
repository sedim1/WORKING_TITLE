#ifndef MESHBUFFER_H
#define MESHBUFFER_H

#include<glad/glad.h>
#include"shader.h"
#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>

//Buffer of a single object
typedef struct mesh
{
	float* buffer; //Actual buffer of mesh (contains vertices positions, vertex textures and normals)
	int bufferSize; //Size of actual buffer
	int bufferVertices; //amount of vertices positions that the buffer has
	unsigned int texture; //single texture
	unsigned int VBO;//VAO STRUCTURE IS: (vx,vy,vz,vtu,vtv,vnx,vny,vnz)
	unsigned int VAO;
	//flags
	bool texLoaded; //Flag to check if the texture
	bool glEnabled; //Flag to check if everything of the mesh has been setted up correctly
	struct mesh *next;
}MESHBUFFER;

//Functions for loading and drawing meshes
MESHBUFFER* loadMeshes(char *objFile,char** imgPath);//Returns ainked list of meshes
MESHBUFFER* createMesh();
void addMesh(MESHBUFFER **meshes,MESHBUFFER *newMesh);
void setUpMesh(MESHBUFFER** mesh,char* imgPath);
void deleteMeshes(MESHBUFFER **meshes);
void drawMeshes(MESHBUFFER* meshes, shaderProgram *p);
void insertSegment(float**buffer,int* bufferPos,float* v,int vIndex,float* vt,int vtIndex,float* vn,int vnIndex);

int findVertexPos(int index);
int findUvPos(int index);


//Texture loading
bool loadTexture(char* imgPath,unsigned int *texture);

//DEBUGGING
float getMeshSizeMB(MESHBUFFER* meshes);//Returns size in MB of all meshes
#endif
