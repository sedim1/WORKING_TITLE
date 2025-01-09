#include"MESHBUFFER.h"
#define STB_IMAGE_IMPLEMENTATION
#include"stb_image.h"

//Creates space so we can pass data to the mesh
MESHBUFFER* createMesh()
{
	MESHBUFFER* mesh=(MESHBUFFER*)malloc(sizeof(MESHBUFFER));
	if(mesh!=NULL)
	{
		mesh->glEnabled = false;
		mesh->buffer=NULL;
		mesh->bufferVertices = 0;
		mesh->next=NULL;
		printf("Mesh has been allocated succesfully\n");
	}
	return mesh;
}

void addMesh(MESHBUFFER** meshes,MESHBUFFER *newMesh)
{
	MESHBUFFER* aux;
	if(*meshes==NULL)
	{
		*meshes = newMesh;
	}
	else
	{
		aux=*meshes;
		while(aux->next)
			aux=aux->next;
		aux->next=newMesh;
	}

	printf("Mesh has been added\n");
}

void deleteMeshes(MESHBUFFER **meshes)
{
	MESHBUFFER* current = *meshes;
	MESHBUFFER* del;
	printf("Deleting meshes\n");
	while(current!=NULL)
	{
		//Delete gl objects if they have been setted up
		if(current->glEnabled)
		{
			glDeleteVertexArrays(1,&current->VAO);
			glDeleteBuffers(1,&current->VBO);
			glDeleteTextures(1,&current->texture);
		}
		if(current->buffer!=NULL)
			free(current->buffer);
		del = current;
		current = current->next;
		free(del);
	}
	*meshes=NULL;
}

MESHBUFFER* loadMeshes(char* objFile,char** imgPath)
{
	MESHBUFFER* meshes = NULL;
	MESHBUFFER* current = NULL;
	float x = 0.0f; float y = 0.0f; float z = 0.0f;
	float u = 0.0f; float v = 0.0f;
	float* tempv = NULL; float* tempvt =NULL; float* tempvn = NULL; //They will store all the vertices in the existing obj
	int totalv =0; int totalvt = 0; int totalvn=0;
	int currentVpos = 0; int currentVtpos = 0; int currentVnpos = 0;
	int bufferPos = 0; int vpos =0; int vtpos = 0; int vnpos =0;
	unsigned int indexv[3], indexvt[3], indexvn[3];
	int currentImg = 0;
	char prefix[5];
	FILE *fp = fopen(objFile,"r");
	char debugName[50];
	if(fp)
	{
		//First round is to check how much space to create for each buffer
		printf("%s was opened\n",objFile);
		while(fscanf(fp,"%s",prefix)!=EOF)//First round is for checking how many vertices, vertex normals and vertex texture for each mesh
		{
			if(strcmp(prefix,"o")==0)
			{
				printf("New object detected!\n");
				current=NULL;
				current=createMesh(); //create mesh
				if(current==NULL) //Ceck if the mesh has been created succesfully
				{
					printf("Could not allocate memory for a new mesh");
					//Delete all meshes that have been created in case a new mesh could not be created
					deleteMeshes(&meshes);
					current=NULL;
					break;
				}
				addMesh(&meshes,current);//Add Mesh to the linked list
			}
			if(strcmp(prefix,"v")==0)
				totalv+=3;
			if(strcmp(prefix,"vn")==0)
				totalvn+=3;
			if(strcmp(prefix,"vt")==0)	
				totalvt+=2;
			if(strcmp(prefix,"f")==0)
				current->bufferSize+= (8*3);
		}
		if(meshes!=NULL)//if meshes had been succesfully created, start reading the data,
		{
			current=NULL;
			fseek(fp,0L,SEEK_SET);//return to the start of the file
			//Allecate memory
			tempv=(float*)malloc(totalv*sizeof(float));
			tempvt=(float*)malloc(totalvt*sizeof(float));
			tempvn=(float*)malloc(totalvn*sizeof(float));

			while(fscanf(fp,"%s",prefix)!=EOF)
			{
				if(strcmp(prefix,"o")==0)
				{
					if(current==NULL)//Acces first mesh
					{
						printf("Passing to first mesh\n");
						fscanf(fp,"%s",debugName);
						printf("o %s\n",debugName);
						current=meshes;
					}
					else
					{// set up current mesh before accessing the next mesh
						printf("BufferELements: %d\n",current->bufferSize);
						setUpMesh(&current,imgPath[currentImg]);
						printf("Mesh %p is assigned texture: %s\n", (void*)current, imgPath[currentImg]);
					 	printf("passing to next mesh\n");
						current=current->next;
						currentImg++;
						fscanf(fp,"%s",debugName);
						printf("o %s\n",debugName);
					}
					printf("Buffer for VBO:\n");
					bufferPos = 0;
					current->buffer=(float*)malloc(current->bufferSize*sizeof(float));
				}
				if(strcmp(prefix,"v")==0)
				{
					fscanf(fp,"%f %f %f",&x,&y,&z);
					tempv[currentVpos]=x; tempv[currentVpos+1]=y; tempv[currentVpos+2]=z;
					//printf("v %f %f %f\n",tempv[currentVpos],tempv[currentVpos+1],tempv[currentVpos+2]);
					currentVpos+=3;
				}
				if(strcmp(prefix,"vt")==0)
				{
					fscanf(fp,"%f %f",&u,&v);
					tempvt[currentVtpos]=u; tempvt[currentVtpos+1]=v;
					//printf("vt %f %f\n",tempvt[currentVtpos],tempvt[currentVtpos+1]);
					currentVtpos+=2;
				}
				if(strcmp(prefix,"vn")==0)
				{
					fscanf(fp,"%f %f %f",&x,&y,&z);
					tempvn[currentVnpos]=x; tempvn[currentVnpos+1]=y; tempvn[currentVnpos+2]=z;
					//printf("vn %f %f %f\n",tempvn[vnpos],tempvn[vnpos+1],tempvn[vnpos+2]);
					currentVnpos+=3;
				}
				if(strcmp(prefix,"f")==0)
				{
					fscanf(fp,"%d/%d/%d %d/%d/%d %d/%d/%d",&indexv[0],&indexvt[0],&indexvn[0],
							&indexv[1],&indexvt[1],&indexvn[1],&indexv[2],&indexvt[2],&indexvn[2]);
					//printf("f %d/%d/%d %d/%d/%d %d/%d/%d\n",indexv[0],indexvt[0],indexvn[0],
						  	//indexv[1],indexvt[1],indexvn[1],indexv[2],indexvt[2],indexvn[2]);
					for(int i = 0; i < 3; i++)
					{
						current->bufferVertices++;
						//acces the memory position of current indexes of vertex, normals and vt's
						indexv[i]-=1;indexvt[i]-=1;indexvn[i]-=1;
						vpos = findVertexPos(indexv[i]);
						vtpos = findUvPos(indexvt[i]);
						vnpos = findVertexPos(indexvn[i]);
						//Insert vertex of indexv i
						current->buffer[bufferPos]=tempv[vpos]; 
						current->buffer[bufferPos+1]=tempv[vpos+1];
						current->buffer[bufferPos+2]=tempv[vpos+2];
						printf("::v %f %f %f :: ",current->buffer[bufferPos],current->buffer[bufferPos+1],
								current->buffer[bufferPos+2]);
						bufferPos+=3;
						//Insert vertex texture of indexvt i
						current->buffer[bufferPos]=tempvt[vtpos];
						current->buffer[bufferPos+1]=tempvt[vtpos+1];
						printf("vt %f %f :: ",current->buffer[bufferPos],current->buffer[bufferPos+1]);
						bufferPos+=2;
						//Insert vertex normal of indexvn i
						current->buffer[bufferPos]=tempvn[vnpos]; 
						current->buffer[bufferPos+1]=tempvn[vnpos+1];
						current->buffer[bufferPos+2]=tempvn[vnpos+2];
						printf("::vn %f %f %f ::\n",current->buffer[bufferPos],current->buffer[bufferPos+1],
							current->buffer[bufferPos+2]);
						bufferPos+=3;
					}

				}
			}
			//Setup last mesh
			if(current!=NULL)
			{
				printf("BufferELements: %d\n",current->bufferSize);
				setUpMesh(&current,imgPath[currentImg]);
			}
			//Unlink and free data we dont need anymore
			free(tempv); free(tempvt); free(tempvn);
			tempv = tempvt = tempvn = NULL;
			current=NULL;
		}
		//If first pass has been passed succesfully
		printf("Closing file\n");
		fclose(fp);

	}
	if(meshes==NULL)
		printf("ERROR::%s could not be loaded\n",objFile);
	else
	{
		printf("%s was loaded succesfully. Size:%f MB\n",objFile,getMeshSizeMB(meshes));
	}
	return meshes;
}

int findVertexPos(int index)
{
	return index * 3;
}

int findUvPos(int index)
{
	return index * 2;
}

void setUpMesh(MESHBUFFER** mesh,char* imgPath)
{
	MESHBUFFER* m = *mesh;
	//Generate VAOS and buffer
	glGenVertexArrays(1,&m->VAO); //Generate vertex Array
	glBindVertexArray(m->VAO);//Bind Vertex array
	//GEN VBO of vertex and link it to the vao
	glGenBuffers(1,&m->VBO);
	glBindBuffer(GL_ARRAY_BUFFER,m->VBO);
	glBufferData(GL_ARRAY_BUFFER,m->bufferSize*sizeof(float),m->buffer,GL_STATIC_DRAW);
	//Enable vertex positions
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)0);
	glEnableVertexAttribArray(0);
	//Vertex Texture enable
	glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);
	//Vertex Normal Enable
	glVertexAttribPointer(2,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(5*sizeof(float)));
	glEnableVertexAttribArray(2);
	//loadTexture
	m->texLoaded = loadTexture(imgPath,&m->texture);
	//Unbind so it wont be modified by other vaos
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER,0);
	m->glEnabled = true;
}

void drawMeshes(MESHBUFFER* meshes,shaderProgram* p)
{
	MESHBUFFER* m = meshes;
	while(m!=NULL)
	{
		glUseProgram(*p);
		glBindVertexArray(m->VAO);
		glActiveTexture(GL_TEXTURE0);
		int location = glGetUniformLocation(*p,"texture1");
		if(location!=-1)
			glUniform1i(location,0);
		glBindTexture(GL_TEXTURE_2D,m->texture);
		glDrawArrays(GL_TRIANGLES,0,m->bufferVertices);//DRAW THE MESH
		glBindVertexArray(0); //UNBIND THE VAO
		glBindTexture(GL_TEXTURE_2D,0);
		m=m->next;
	}
}

//Texture handling
bool loadTexture(char* imgPath,unsigned int *texture)//Currently each mesh can handle one single texture
{
	printf("Loading %s texture...\n",imgPath);
	unsigned char *data;
	int width, height, nrChannels;
	glGenTextures(1,texture);
	glBindTexture(GL_TEXTURE_2D,*texture);
	//Setting parameters doe weapping/filtering
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	//load and generate the texture
	printf("Loading image....\n");
	stbi_set_flip_vertically_on_load(true);
	data = stbi_load(imgPath,&width,&height,&nrChannels,0);
	if(data)
	{
		printf("Image found::nrChanels %d::width %d::height %d\n",nrChannels,width,height);
		if (nrChannels == 3)
    			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		else if (nrChannels == 4)
    			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		printf("Generating mipmap...\n");
		glGenerateMipmap(GL_TEXTURE_2D);

	}
	else
	{
		stbi_image_free(data);
		printf("ERROR::Failed to load %s texture\n",imgPath);
		return false;
	}
	stbi_image_free(data);
	printf("LOADED %s TEXTURE SUCCESFULLY\n",imgPath);
	return true;
}

//Debuging functions
float getMeshSizeMB(MESHBUFFER* meshes)
{
	float mb = 0.0f;
	MESHBUFFER* current = meshes;
	while(current!=NULL)
	{
		mb += 0.000001f * (sizeof(current->buffer));
		current=current->next;
	}
	return mb;
}

