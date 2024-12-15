#ifndef CAMERA_H
#define CAMERA_H

#include<GLFW/glfw3.h>
#include<cglm/cglm.h>
#include<stdbool.h>
#include"radians.h"

typedef struct
{
	vec3 cameraPos; //camera position
	vec3 cameraFront; //camera direction
	vec3 cameraUp;
	bool firstmouse;
	float fov;
	float sensitivity;
	float pitch;
	float yaw;
	float roll;
}CAMERA;

//view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
void cameraControl(CAMERA *cam,GLFWwindow *window);
void updateFrontVector(CAMERA *cam,GLFWwindow *window);
void updateViewMatrix(CAMERA *cam,mat4 view);
void mouse_callback(GLFWwindow *window,double xpos,double ypos);
#endif
