#ifndef PHYSICS_H
#define PHYSICS_H

#include "ENTITIES.h"
#include <cglm/cglm.h>
#include <stdlib.h>
#include <stdio.h>

enum BODYTYPE{
	STATICBODY, //Can interact with other entities, but wont affect the entity itself
	RIGIDBODY, //Can be affected by other entities and interact - will be run by general code
	KINEMATIC_BODY //Can use functions of physics engine, but will be more controlled by specific code
};

enum COLLIDERTYPE{
	PLANE,
	SPHERE,
	CUBE
};

typedef struct
{
	ENTITY3D* entity;
	float mass;
	float Fy;
	float Fx;
	vec3 velocity;
	enum BODYTYPE type;
}PHYSICSOBJ; //These are not dynamically allocated, they already exist on memory

typedef struct phworld
{
	PHYSICSOBJ *object;
	struct phworld* next;
}PHYSICSWORLD;

void physicsProcessWorld(PHYSICSWORLD* world,float deltaTime,float gravity);
void addObjectToWorld(PHYSICSWORLD** world,PHYSICSOBJ* physicsObject);
void clearWorld(PHYSICSWORLD** world);
PHYSICSWORLD* instanceObject(PHYSICSOBJ* physicsObject); //creates the physic object object in the world

#endif
