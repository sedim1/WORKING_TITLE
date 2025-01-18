#include "OBJTRANSFORMATIONS.h"

SPATIAL_ATTRIBUTES spatialAttributes()
{
	SPATIAL_ATTRIBUTES attributes;
	glm_vec3_zero(attributes.pivot);
	glm_vec3_zero(attributes.position);
	glm_vec3_zero(attributes.size);
	attributes.yaw = attributes.pitch = attributes.roll = 0.0f;
	return attributes;
}

void manipulateAttributes(SPATIAL_ATTRIBUTES* A, mat4 modelMatrix)
{
	vec3 negativePivot;
	glm_vec3_negate_to(A->pivot,negativePivot);
	mat4 tOrigin, tPos, scale, rz, ry, rx, tFront, aux;
	//SETUP MATRICES
	glm_mat4_identity(aux);
	glm_translate(tOrigin,negativePivot);
	glm_translate(tFront,A->pivot);
	glm_scale(scale,A->size);
	glm_rotated_x(aux,degToRad(&A->pitch),rx);
	glm_rotated_y(aux,degToRad(&A->yaw),ry);
	glm_rotated_z(aux,degToRad(&A->roll),rz);
	//GENERATE MODEL MATRIX
	glm_mat4_mulN((mat4 *[]){&tPos,&scale,&tFront,&rz,&ry,&rx,&tOrigin},7,modelMatrix);
}
