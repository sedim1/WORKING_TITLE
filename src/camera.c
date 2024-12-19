#include"camera.h"

void cameraControl(CAMERA *cam,GLFWwindow* window)
{
	float cameraSpeed = 0.05f;

	updateFrontVector(cam,window);

	if(glfwGetKey(window,GLFW_KEY_E)==GLFW_PRESS)
		cam->cameraPos[1]+=cameraSpeed;

	if(glfwGetKey(window,GLFW_KEY_Q)==GLFW_PRESS)
		cam->cameraPos[1]-=cameraSpeed;
	
	if(glfwGetKey(window,GLFW_KEY_W) == GLFW_PRESS)//MOVE FORWARD
	{
		//cameraPos += cameraSpeed * cameraFront;
		vec3 aux, res;
		glm_vec3_scale(cam->cameraFront,cameraSpeed,aux);
		glm_vec3_add(cam->cameraPos,aux,res);
		glm_vec3_copy(res,cam->cameraPos);
	}
	if(glfwGetKey(window,GLFW_KEY_S) == GLFW_PRESS)//MOVE BACKWARD
	{
		//cameraPos -= cameraSpeed * cameraFront;
		vec3 aux, res;
		glm_vec3_scale(cam->cameraFront,cameraSpeed,aux);
		glm_vec3_sub(cam->cameraPos,aux,res);
		glm_vec3_copy(res,cam->cameraPos);
	}
	if(glfwGetKey(window,GLFW_KEY_A) == GLFW_PRESS)//MOVE LEFT
	{
		//Operation doin here
		//cameraPos -= normalized(cross(cameraFront,cameraUp)) * cameraFront;
		vec3 res, aux;
		glm_vec3_crossn(cam->cameraFront,cam->cameraUp,aux);
		glm_vec3_scale(aux,cameraSpeed,aux);
		glm_vec3_sub(cam->cameraPos,aux,res);
		glm_vec3_copy(res,cam->cameraPos);
	}
	if(glfwGetKey(window,GLFW_KEY_D) == GLFW_PRESS)//MOVE RIGHT
	{
		//Operation doin here
		//cameraPos += normalized(cross(cameraFront,cameraUp)) * cameraFront;
		vec3 res, aux;
		glm_vec3_crossn(cam->cameraFront,cam->cameraUp,aux);
		glm_vec3_scale(aux,cameraSpeed,aux);
		glm_vec3_add(cam->cameraPos,aux,res);
		glm_vec3_copy(res,cam->cameraPos);
	}
}

void updateFrontVector(CAMERA* cam,GLFWwindow* window)
{
	float offsett = 1.0f;

	if(glfwGetKey(window,GLFW_KEY_RIGHT)==GLFW_PRESS) //TURN RIGHT the yaw
		cam->yaw+=offsett;
	if(glfwGetKey(window,GLFW_KEY_LEFT)==GLFW_PRESS) //TURN LEFT the yaw
		cam->yaw-=offsett;

	if(glfwGetKey(window,GLFW_KEY_UP)==GLFW_PRESS)//Look Up
		cam->pitch+=offsett;
	if(glfwGetKey(window,GLFW_KEY_DOWN)==GLFW_PRESS)//Look Up
		cam->pitch-=offsett;

	if(cam->pitch>89.0f)
		cam->pitch = 89.0f;
	if(cam->pitch < -89.0f)
		cam->pitch = -89.0f;

	//Update the camera direction
	cam->cameraFront[0] = cos(degToRad(&(cam->yaw))) * cos(degToRad(&(cam->pitch)));	
	cam->cameraFront[1] = sin(degToRad(&(cam->pitch)));	
	cam->cameraFront[2] = sin(degToRad(&(cam->yaw))) * cos(degToRad(&(cam->pitch)));
	glm_vec3_normalize(cam->cameraFront);
}

void updateViewMatrix(CAMERA *cam,mat4 view)
{
	vec3 center; //center = camerapos + camera front (point looking at)
	glm_vec3_add(cam->cameraPos,cam->cameraFront,center);
	glm_lookat(cam->cameraPos,center,cam->cameraUp,view);
}

void mouse_callBack(GLFWwindow *window,double xpos, double ypos)
{
	//Get the camera struct associated to the window
	CAMERA* cam = (CAMERA*)glfwGetWindowUserPointer(window);


	//Update the camera direction
	cam->cameraFront[0] = cos(degToRad(&(cam->yaw))) * cos(degToRad(&(cam->pitch)));	
	cam->cameraFront[1] = sin(degToRad(&(cam->pitch)));	
	cam->cameraFront[2] = sin(degToRad(&(cam->yaw))) * cos(degToRad(&(cam->pitch)));	
}
