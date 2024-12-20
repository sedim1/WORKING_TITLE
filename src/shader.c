#include"shader.h"

char* loadShaderFile(char *filePath)
{
	char *shader = NULL;

	//OPEN FILE
	FILE *fp = fopen(filePath,"r");

	if(fp)
	{
		//Get the size of the shader file
		fseek(fp,0,SEEK_END);
		int size = ftell(fp);
		rewind(fp);
		//printf("FileSize: %d\n",size);
		//Read the shader file
		shader = (char*)malloc(sizeof(char)*size+1);
		if(!shader)
			return NULL;
		fread(shader,1,size,fp);
		shader[size] = '\0';
		//printf("ShaderFile Loaded:\n%s",shader);

		fclose(fp);
	}

	return shader;
}

TShader *createShader(char *filePath, GLenum shaderType)
{
	int success;
	char infoLog[512];
	TShader *new = NULL;
	new = (TShader*)malloc(sizeof(TShader)); //Allocate memory for the shader
	const char *shaderSource = loadShaderFile(filePath); //Load file
	if(new&&shaderSource)
	{
		new->source = glCreateShader(shaderType);
		new->next = NULL;
		//CompileShader
		glShaderSource(new->source,1,&shaderSource,NULL);
		glCompileShader(new->source);
		glGetShaderiv(new->source,GL_COMPILE_STATUS,&success);
		//check if compilation was succesfull
		if(!success)
		{
			glGetShaderInfoLog(new->source,512,NULL,infoLog);
			printf("ERROR::SHADER::COMPILATION_FAILED\n%s",infoLog);
			exit(-1);
		}
		printf("::SHADER COMPILED SUCCESFULLY::\n");
	}

	return new;
}

void addShader(TShader **shaders,char *filePath,GLenum shaderType)
{
	TShader *current;
	if(*shaders == NULL)
	{
		*shaders = createShader(filePath,shaderType);
	}
	else
	{
		current = *shaders;
		while(current->next!=NULL)
			current = current->next;
		current->next = createShader(filePath,shaderType);
	}
}

shaderProgram createShaderProgram(char *shaderSources[],GLenum types[],int n)
{
	int success;
	char infoLog[512];
	shaderProgram program;
	TShader *sources = NULL;
	//Load shaders
	for(int i = 0;i<n;i++)
	{
		addShader(&sources,shaderSources[i],types[i]);
	}
	//Attach the shaders to the shader Program
	program = glCreateProgram();
	TShader *current = sources;
	while(current)
	{
		glAttachShader(program,current->source);
		current = current->next;
	}
	glLinkProgram(program);
	//Check if the shader was created succesfully
	glGetProgramiv(program,GL_LINK_STATUS,&success);
	if(!success)
	{
		glGetProgramInfoLog(program,512,NULL,infoLog);
		printf("ERROR::LINKING_SHADER_PROGRAM::\n%s",infoLog);
		exit(-1);
	}
	printf("::SHADER PROGRAM CREATED SUCCESFULLY!!::\n");
	deleteShaders(&sources);
	return program;
}

void deleteShaders(TShader **shaders)
{
	TShader *current = *shaders;
	TShader *del = NULL;
	do
	{
		//delete shaders and free the space
		glDeleteShader(current->source);
		del = current;
		if(current->next)
			current = current->next;
		free(del);
	}while(current->next);
	*shaders = NULL;
}

void deleteShaderProgram(shaderProgram *program)
{
	glDeleteProgram(*program);
}

//uniform funcitons
void updateMatrix4(shaderProgram *program,mat4 matrix,char* name)
{
	glUseProgram(*program);
	int location;
	//find location and verify if exist
	if((location = glGetUniformLocation(*program,name))==-1)
	{
		printf("UNIFORM %s is not found\n",name);
		exit(-1);
	}
	//Update the matrix
	glUniformMatrix4fv(location,1,GL_FALSE,(float*)matrix);
}

