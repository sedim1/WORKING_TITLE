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
			printf("MODEL: %s\n",model);//Model that was loaded
			for(int i = 0; i < textures.size;i++)
			{
				printf("TEXTURE: %s\n",textures.strings[i]);//TEXTURE THAT WERE READEN
			}
			entity->model=loadMeshes(model,textures.strings);
			eraseStrings(&textures);
		}
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
}

