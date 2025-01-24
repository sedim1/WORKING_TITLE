#include "OBJTRANSFORMATIONS.h"

SPATIAL_ATTRIBUTES spatialAttributes()
{
	SPATIAL_ATTRIBUTES attributes;
	glm_vec3_zero(attributes.pivot);
	glm_vec3_zero(attributes.position);
	glm_vec3_one(attributes.size);
	attributes.yaw = attributes.pitch = attributes.roll = 0.0f;
	glm_mat4_identity(attributes.model);
	return attributes;
}

void updateModelMatrix(SPATIAL_ATTRIBUTES* A) //This model matrix will rotate, traslate and scale
{
	vec3 negativePivot;
	glm_vec3_negate_to(A->pivot,negativePivot);
	glm_mat4_identity(A->model);
	// model = move to pivot * scale * rotate * translate * move to origin
	glm_translate(A->model,A->position);
	glm_scale(A->model,A->size);
	glm_translate(A->model,A->pivot);
	glm_rotate_z(A->model,degToRad(&(A->roll)),A->model); 
	glm_rotate_y(A->model,degToRad(&(A->pitch)),A->model);
	glm_rotate_x(A->model,degToRad(&(A->yaw)),A->model);
	glm_translate(A->model,negativePivot);
}
