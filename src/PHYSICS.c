#include "PHYSICS.h"
#define MAX_FALL_SPEED 10

void physicsProcessWorld(PHYSICSWORLD* world,float deltaTime, float gravity)
{
	PHYSICSWORLD* w = world;
	vec3 velocityDelta;
	while(w!=NULL)
	{
		if(w->object->type==RIGIDBODY)
		{
			//Apply gravity to objects - Step 1
			if(w->object->applyGravity)
				w->object->velocity[1] += gravity * deltaTime; //Applying gravity to object
			else
				w->object->velocity[1] = 0;
			//Run specific code defined by the KINEMATIC BODY Step 1.1

		}
		//Update the position according to the velocity of the object - Step 2
		glm_vec3_add(w->object->entity->properties.position,w->object->velocity,w->object->entity->properties.position);

		//Collision detection
		w = w->next;
	}
}

void addObjectToWorld(PHYSICSWORLD** world,PHYSICSOBJ* physicsObject)
{
	PHYSICSWORLD* current = *world;
	if(current==NULL)
	{
		*world = instanceObject(physicsObject);
	}
	else
	{
		while(current!=NULL)
			current = current->next;
		current = instanceObject(physicsObject);
	}
}

PHYSICSWORLD* instanceObject(PHYSICSOBJ* physicsObject)
{
	PHYSICSWORLD* obj=(PHYSICSWORLD*)malloc(sizeof(PHYSICSWORLD));
	if(obj==NULL)
	{printf("ERROR!! COULD NOT ALLOCATE MEMORY FOR PHYSICS OBJECT!!\n"); return NULL;}
	else
	{
		obj->object=physicsObject;
		glm_vec3_zero(obj->object->velocity);
		glm_vec3_zero(obj->object->forces);
		obj->next=NULL;
	}

	return obj;
}

void clearWorld(PHYSICSWORLD** world)
{
	PHYSICSWORLD* w = *world;
	PHYSICSWORLD* del;
	while(w!=NULL)
	{
		del = w;
		w->object->entity = NULL;
		w->object = NULL;
		w = w->next;
		free(del);
	}
}
