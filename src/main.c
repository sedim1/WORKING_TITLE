#include<stdio.h>
#include<stdlib.h>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include"shader.h"

int width = 800;
int height = 600;

GLFWwindow* window;

GLenum types[2] = {GL_VERTEX_SHADER,GL_FRAGMENT_SHADER};
char *shaderSources[2] = {"./SHADERS/vertexShader.glsl","./SHADERS/fragmentShader.glsl"};

shaderProgram program;

void resizeWindow(GLFWwindow* win,int w, int h);

float vertices[] = {
	-0.5f,-0.5f,0.0f,
	0.5f,-0.5f,0.0f,
	0.0f,0.5f,0.0f,
};

int main(int argc,char* argv[])
{;;
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

	deleteShaders(&program.sources);

	//LOAD VBO, VAO 
	unsigned int VBO, VAO;
	glGenBuffers(1,&VBO);
	glGenVertexArrays(1,&VAO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);//Pass the data to the buffer
	//Enable atribute to the vertex array
	glVertexAttribPointer(0,3,GL_FLOAT,GL_TRUE,3*sizeof(float),(void*)0);
	glEnableVertexAttribArray(0);
	
	//Start window
	glViewport(0,0,width,height);

	//Set events
	glfwSetFramebufferSizeCallback(window,resizeWindow);


	//main loop
	while(!glfwWindowShouldClose(window))
	{

		if(glfwGetKey(window,GLFW_KEY_ESCAPE)==GLFW_PRESS)
			glfwSetWindowShouldClose(window,true);

		glUseProgram(program.id);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES,0,3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	deleteShaderProgram(&program);
	glfwTerminate();

	exit(0);
}

void resizeWindow(GLFWwindow *win,int w, int h)
{
	glViewport(0,0,w,h);
}
