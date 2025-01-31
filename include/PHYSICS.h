#ifndef PHYSICS_H
#define PHYSICS_H

#include "ENTITIES.h"
#include <cglm/cglm.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

enum BODYTYPE{
	STATICBODY, //WILL NOT BE AFFECTED BY GRAVITY AND FORCE
	RIGIDBODY, //WILL BE AFFECTED BY GRAVITY AND FORCE
	KINEMATICBODY, //WILL BE CONTROLLED VIA CODE
};

enum COLLIDERSHAPE{
	BOX,
	CAPSULE,
	SPHERE
};

typedef struct{
	float MinX;
	float MaxX;
	float MinY;
	float MaxY;
	float MinZ;
	float MaxZ;
}BOX_COLLIDER;

typedef struct{
	float radious;
}SPHERE_COLLIDER;

typedef struct{
	float radious;
	float height;
}CAPSULE_COLLIDER;

typedef struct{
	ENTITY3D* entity; //Follow the entity the collider is attached to;
	void* shape;
	enum COLLIDERSHAPE type;
}COLLIDER;

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

//General physics stuff to process in all objects attache to te current world
void physicsProcessWorld(PHYSICSWORLD* world,float deltaTime,float gravity);//
void addObjectToWorld(PHYSICSWORLD** world,PHYSICSOBJ* physicsObject);//
void clearWorld(PHYSICSWORLD** world);//
PHYSICSWORLD* instanceObject(PHYSICSOBJ* physicsObject); //creates the physic object object in the world

#endif
