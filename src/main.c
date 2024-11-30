#include<stdio.h>
#include<stdlib.h>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include"shader.h"

int width = 800;
int height = 600;

GLFWwindow* window;

void resizeWindow(GLFWwindow* win,int w, int h);

int main(int argc,char* argv[])
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);
	
	printf("Initialized glfw\n");

	window = glfwCreateWindow(width,height,"3D_GAME",NULL,NULL);

	if(!window)
	{
		printf("Error: Window has not been created succesfully\n");
		exit(-1);
	}

	glfwMakeContextCurrent(window);

	//LOAD OPENGL FUNCTIONS
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("Error: Failed to load glad!\n");
		exit(-1);
	}

	char *shaderTestFile = loadShaderFile("./SHADERS/vertexShader.glsl");

	//Start window
	glViewport(0,0,width,height);

	//Set events
	glfwSetFramebufferSizeCallback(window,resizeWindow);


	//main loop
	while(!glfwWindowShouldClose(window))
	{
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	exit(0);
}

void resizeWindow(GLFWwindow *win,int w, int h)
{
	glViewport(0,0,w,h);
}
