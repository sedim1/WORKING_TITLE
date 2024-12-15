#include<stdio.h>
#include<stdlib.h>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include"shader.h"
#include <cglm/cglm.h>
#include "radians.h"
#include "camera.h"

void resizeWindow(GLFWwindow* win,int w, int h);
void init();
void display();
void mainLoop();
void display();
void update();
void end();

int width = 800;
int height = 600;

GLFWwindow* window;

GLenum types[2] = {GL_VERTEX_SHADER,GL_FRAGMENT_SHADER};
char *shaderSources[2] = {"./SHADERS/vertexShader.glsl","./SHADERS/fragmentShader.glsl"};

shaderProgram program;

CAMERA camera;

mat4 V;
mat4 P;


unsigned int VBO, VAO, EBO;

float vertices[] = {
	//Vertices
	0.5f,0.5f,0.0f,  
	0.5f,-0.5f,0.0f, 
	-0.5f,-0.5f,0.0f,
	-0.5f,0.5f, 0.0f, 
};

unsigned int indices[] ={
	0,1,3,
	1,2,3
};

int main(int argc,char* argv[])
{
	init();
	//main loop
	mainLoop();

	end();

	exit(0);
}

void resizeWindow(GLFWwindow *win,int w, int h)
{
	glViewport(0,0,w,h);
}

void mainLoop()
{
	while(!glfwWindowShouldClose(window))
	{
		//Clear the screen to this color
		glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
        	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		if(glfwGetKey(window,GLFW_KEY_ESCAPE)==GLFW_PRESS)
			glfwSetWindowShouldClose(window,true);
		//Process game logic here
		update();
		//Render stuff here
		display();
		//Swap buffers and process events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void update()//function for writing the logic here
{
	cameraControl(&camera,window);

	glUseProgram(program);
	
	//Update lookat camera
	updateViewMatrix(&camera,V);
	
	//Update uniforms
	glUniformMatrix4fv(glGetUniformLocation(program,"proj"),1,GL_FALSE,(float*)P);
	glUniformMatrix4fv(glGetUniformLocation(program,"view"),1,GL_FALSE,(float*)V);
}

void display()
{
	//Render stuff here
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
	glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
}

void init()
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

	//LOAD SHADERS
	program = createShaderProgram(shaderSources,types,2);

	//LOAD VBO, VAO 
	glGenVertexArrays(1,&VAO);
	glGenBuffers(1,&VBO);
	glGenBuffers(1,&EBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);//Pass the data to the buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);
	
	//Enable atribute to the vertex array
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
	glEnableVertexAttribArray(0);
	
	//Start window
	glViewport(0,0,width,height);

	//Set events
	glfwSetFramebufferSizeCallback(window,resizeWindow);

	//start camera
	camera.cameraPos[0]=0.0f; camera.cameraPos[1]=0.0f; camera.cameraPos[2]=3.0f;
	camera.cameraFront[0]=0.0f; camera.cameraFront[1]=0.0f; camera.cameraFront[2]= -1.0f;
	camera.cameraUp[0]=0.0f; camera.cameraUp[1]=1.0f; camera.cameraUp[2]=0.0f;
	camera.pitch = 0.0f;
	camera.yaw = -90.0f;
	camera.roll = 0.0f;
	camera.fov = 45.0f;

	//start matrices
	updateViewMatrix(&camera,V);
	glm_perspective(degToRad(&(camera.fov)),(float)width/(float)height,0.1f,100.0f,P);
}

void end()
{
	glDeleteVertexArrays(1,&VAO);
	glDeleteBuffers(1,&VBO);
	glDeleteBuffers(1,&EBO);
	deleteShaderProgram(&program);
	glfwTerminate();
}
