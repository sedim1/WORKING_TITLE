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
		printf("FileSize: %d\n",size);
		//Read the shader file
		shader = (char*)malloc(sizeof(char)*size+1);
		if(!shader)
			return NULL;
		fread(shader,1,size,fp);
		shader[size] = '\0';
		printf("ShaderFile Loaded:\n%s",shader);

		fclose(fp);
	}

	return shader;
}
