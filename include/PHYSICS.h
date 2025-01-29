#ifndef PHYSICS_H
#define PHYSICS_H

#include "ENTITIES.h"
#include <cglm/cglm.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

enum BODYTYPE{
	STATICBODY, //
	RIGIDBODY, //WILL BE AFFECTED BY GRAVITY AND FORCES
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
	vec3 forces;
	vec3 velocity;
	bool applyGravity;
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
