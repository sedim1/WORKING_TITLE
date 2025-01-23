#ifndef ENTITIES_H
#define ENTITIES_H

#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include"MESHBUFFER.h"
#include"OBJTRANSFORMATIONS.h"

typedef struct{
	char** strings;
	int size;
}STR_ARRAY;

typedef struct
{
	MESHBUFFER* model; //Meshes forming the model
	SPATIAL_ATTRIBUTES properties; //3D space properties
}ENTITY3D;

ENTITY3D createEntity3D(char* modelPath); //Start entity with a model or without it;

#endif
