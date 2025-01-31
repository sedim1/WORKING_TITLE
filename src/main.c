#include<stdio.h>
#include<stdlib.h>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include"shader.h"
#include <cglm/cglm.h>
#include "radians.h"
#include "camera.h"
#include "OBJTRANSFORMATIONS.h"
#include "ENTITIES.h"
#include "PHYSICS.h"
#include "DELTATIME.h"

void resizeWindow(GLFWwindow* win,int w, int h);
void init();
void loadWorld();
void display();
void mainLoop();
void display();
void update(float steps);
void end();

DELTATIME deltaTimeFPS;
int FPS=0;


int width = 800;
int height = 600;

GLFWwindow* window;

GLenum types[2] = {GL_VERTEX_SHADER,GL_FRAGMENT_SHADER};
char *shaderSources[2] = {"./SHADERS/vertexShader.glsl","./SHADERS/fragmentShader.glsl"};


shaderProgram program;

CAMERA camera;

mat4 V;
mat4 P;

float gravity = -5.81f;

ENTITY3D plane;
ENTITY3D entity1;
PHYSICSOBJ object;
PHYSICSWORLD* world;

int main(int argc,char* argv[])
{
	init();
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
	int frames=0;
	float tAccumulator = 0.0;
	float tSlice = 1.0f/60.0f;//Time we define here, the time we want to be elapsed between updates
	float steps = 1.0f/1000.0f;
	DELTATIME loopCycle = {0.0f,0.0f,0.0f};

	while(!glfwWindowShouldClose(window))
	{
		updateDeltaTime(&loopCycle); //For handling the game states
		loopCycle.lastTime+=loopCycle.delta; //Last update
		tAccumulator+=loopCycle.delta;
		countTime(&loopCycle);
		countTime(&deltaTimeFPS);//Start countingtime for FPS
		//Clear the screen to this color
		glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
        	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		if(glfwGetKey(window,GLFW_KEY_ESCAPE)==GLFW_PRESS)
			glfwSetWindowShouldClose(window,true);
		//Update game states and logic here
		while(tAccumulator > tSlice)
		{
			update(steps);
			tAccumulator -= tSlice;
		}

		//Render stuff here
		display();
		updateDeltaTime(&deltaTimeFPS);//Update the delta time for FPS
		frames++;
		if(deltaTimeFPS.delta > 1.0f)
		{
			//UPDATE FPS
			FPS = frames;
			frames=0;
			saveLastTime(&deltaTimeFPS);
			printf("FPS: %d\n",FPS);
		}

		//Swap buffers and process events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
}

void update(float steps)//function for writing the logic here
{
	cameraControl(&camera,window);

	physicsProcessWorld(world,steps,gravity);

	glUseProgram(program);
	//Update lookat camera
	updateViewMatrix(&camera,V);
	//Update matrices
	updateMatrix4(&program,P,"proj");
	updateMatrix4(&program,V,"view");
}

void display()
{ 
	//Render stuff here
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	drawEntity(&plane,&program);
	drawEntity(&entity1,&program);
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

	loadWorld();
	
	glEnable(GL_DEPTH_TEST);

	//Start window
	glViewport(0,0,width,height);

	//Set events
	glfwSetFramebufferSizeCallback(window,resizeWindow);

	//start camera
	camera.cameraPos[0]=0.0f; camera.cameraPos[1]=0.0f; camera.cameraPos[2]=8.0f;
	camera.cameraFront[0]=0.0f; camera.cameraFront[1]=0.0f; camera.cameraFront[2]= -1.0f;
	camera.cameraUp[0]=0.0f; camera.cameraUp[1]=1.0f; camera.cameraUp[2]=0.0f;
	camera.pitch = 0.0f;
	camera.yaw = -90.0f;
	camera.roll = 0.0f;
	camera.fov = 45.0f;

	//start matrices
	updateViewMatrix(&camera,V);
	glm_perspective(degToRad(&(camera.fov)),(float)width/(float)height,0.1f,100.0f,P);

	//Set Global Delta time
	deltaTimeFPS.currentTime = 0.0f;
	deltaTimeFPS.lastTime = 0.0f;
	deltaTimeFPS.delta = 0.0f;
}

void end()
{
	deleteShaderProgram(&program);
	entityClearModel3D(&plane);
	entityClearModel3D(&entity1);
	clearWorld(&world);
	glfwTerminate();
}

void loadWorld()
{
	//LOAD ENTITIES
	plane = createEntity3D();
	entitySetModel3D(&plane,"ENTITIES/plane.model");
	plane.properties.position[1]=-78.0f;


	entity1 = createEntity3D();
	entitySetModel3D(&entity1,"ENTITIES/cube.model");
	object.entity= &entity1;
	object.type = RIGIDBODY;
	object.mass = 1.0f;
	object.applyGravity = true;
	addObjectToWorld(&world,&object);
}
