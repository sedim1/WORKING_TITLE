#ifndef ENTITIES_H
#define ENTITIES_H

#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include"MESHBUFFER.h"
#include"OBJTRANSFORMATIONS.h"
#include"STRARRAY.h"

typedef struct
{
	MESHBUFFER* model; //Meshes forming the model
	SPATIAL_ATTRIBUTES properties; //3D space properties
}ENTITY3D;

ENTITY3D createEntity3D();
void entitySetModel3D(ENTITY3D* entity,char* modelPath); //set 3d model to obj
void entityClearModel3D(ENTITY3D* entity);

#endif
