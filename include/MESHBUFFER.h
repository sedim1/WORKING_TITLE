#ifndef MESHBUFFER_H
#define MESHBUFFER_H

#include<glad/glad.h>
#include"shader.h"
#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct
{
	float *buffer;//contains the actual buffer
	unsigned int size;//elements that the buffer has
}VERTEXBUFFER;

typedef struct
{
	unsigned int *buffer;//contains the actual buffer
	unsigned int size;//elements that the buffer has
}INDEXBUFFER;

//Buffer of a single object
typedef struct mesh
{
	VERTEXBUFFER v; //Store vertex positions
	VERTEXBUFFER vn; //Store normals
	VERTEXBUFFER vt; //Store texture cordinates
	INDEXBUFFER indices;//Store vertex position indices;
	unsigned int texture; //single texture
	unsigned int VBO[3];//3 different vbos for each vertex attribute (one for positions,normals,and teexture coordinates)
	unsigned int VAO;
	unsigned int EBO;
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

//Texture loading
bool loadTexture(char* imgPath,unsigned int *texture);

//DEBUGGING
float getMeshSizeMB(MESHBUFFER* meshes);//Returns size in MB of all meshes
#endif
