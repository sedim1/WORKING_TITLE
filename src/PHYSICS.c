#include "PHYSICS.h"
#define MAX_FALL_SPEED 10

void physicsProcessWorld(PHYSICSWORLD* world,float deltaTime, float gravity)
{
	PHYSICSWORLD* w = world;
	vec3 velocityDelta;
	while(w!=NULL)
	{
		//Apply gravity to objects
		w->object->Fy = w->object->mass * gravity;

		if(w->object->mass>0.0f)
			w->object->velocity[1] += (w->object->Fy/w->object->mass) * deltaTime;

		glm_vec3_add(w->object->entity->properties.position,w->object->velocity,w->object->entity->properties.position);
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
