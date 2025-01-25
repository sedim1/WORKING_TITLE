#include "ENTITIES.h"

void entitySetModel3D(ENTITY3D* entity,char* modelPath)
{
	FILE *fp;
	char prefix[15];
	char texStr[50];
	char model[50]="";
	char** temp;
	char** old;
	STR_ARRAY textures;
	textures.strings=NULL;
	textures.size=0;
	fp=fopen(modelPath,"r");
		if(fp)
		{
			while(fscanf(fp,"%s",prefix)!=EOF)
			{
				if(strcmp(prefix,"MODEL")==0)
					fscanf(fp,"%s",model);
				else if(strcmp(prefix,"TEXTURE")==0)
				{
					//Read texture path
					fscanf(fp,"%s",texStr);
					addString(&textures,texStr);
				}
			}
			fclose(fp);
		
			//Debug information
			entity->id=extractFileName(model);
			printf("MODEL: %s\n",entity->id);//Model that was loaded
			for(int i = 0; i < textures.size;i++)
			{
				printf("TEXTURE: %s\n",textures.strings[i]);//TEXTURE THAT WERE READEN
			}
			entity->model=loadMeshes(model,textures.strings);
			eraseStrings(&textures);
		}
}

void drawEntity(ENTITY3D* entity,shaderProgram* program)
{
	//Update model matrix according to its spatial atributes and to the shader
	updateModelMatrix(&(entity->properties));
	updateMatrix4(program,entity->properties.model,"model");
	drawMeshes(entity->model,program);
}

ENTITY3D createEntity3D()
{
	ENTITY3D entity;
	entity.model=NULL;
	entity.properties = spatialAttributes();
	return entity;
}

void entityClearModel3D(ENTITY3D* entity)
{
	deleteMeshes(&(entity->model));
	free(entity->id);
}

