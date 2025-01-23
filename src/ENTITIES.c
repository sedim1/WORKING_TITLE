#include "ENTITIES.h"

ENTITY3D createEntity3D(char* modelPath)
{
	ENTITY3D entity;
	FILE *fp;
	char prefix[15];
	char texStr[50];
	char model[50]="";
	char** temp;
	STR_ARRAY textures;
	entity.model=NULL;
	entity.properties = spatialAttributes();
	textures.strings=NULL;
	textures.size=0;

	if(modelPath!=NULL)
	{
		fp=fopen(modelPath,"r");
		if(fp)
		{
		
			while(fscanf(fp,"%s",prefix)!=EOF)
			{
				if(strcmp(prefix,"MODEL")==0)
					fscanf(fp,"%s",model);
				else if(strcmp(prefix,"TEXTURE")==0)
				{
					textures.size++;
					if(textures.size==1)
						textures.strings=(char**)malloc(sizeof(char*) * textures.size);
					else
					{
						temp=realloc(textures.strings,sizeof(char*) * textures.size);
					}
					//Read texture path
					fscanf(fp,"%s",texStr);
				}
			}
			fclose(fp);
		}
	}
	return entity;
}
