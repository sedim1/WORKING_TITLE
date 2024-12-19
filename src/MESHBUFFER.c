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
		mesh->v.buffer=NULL; mesh->v.size=0;
		mesh->vn.buffer=NULL; mesh->vn.size=0;
		mesh->vt.buffer=NULL; mesh->vt.size=0;
		mesh->indices.buffer=NULL; mesh->indices.size=0;
		mesh->next=NULL;
		printf("Mesh has been allocated succesfully\n");
	}
	return mesh;
}

void addMesh(MESHBUFFER** meshes,MESHBUFFER *newMesh)
{
	MESHBUFFER* current;
	if(*meshes==NULL)
	{
		*meshes = newMesh;
	}
	else
	{
		current = *meshes;
		while(current->next!=NULL)
			current = current->next;
		current->next = newMesh;
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
			glDeleteBuffers(1,&current->VBO[0]);
			glDeleteBuffers(1,&current->VBO[1]);
			glDeleteBuffers(1,&current->VBO[2]);
			glDeleteBuffers(1,&current->EBO);
			glDeleteTextures(1,&current->texture);
		}
		free(current->v.buffer);
		free(current->vn.buffer);
		free(current->vt.buffer);
		free(current->indices.buffer);
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
	FILE *fp = fopen(objFile,"r");
	float x = 0.0f; float y = 0.0f; float z = 0.0f;
	float u = 0.0f; float v = 0.0f;
	int vPos = 0; int vnPos = 0; int vtPos = 0; int iPos = 0;
	unsigned int index[9];
	int currentImg = 0;
	char prefix[5];
	int newSize;


	if(fp)
	{
		//First round is to check how much space to create for each buffer
		printf("%s was opened\n",objFile);
		while(fscanf(fp,"%s",prefix)!=EOF)
		{
			if(strcmp(prefix,"o")==0)
			{
				printf("New object detected!\n");
				if(current!=NULL)
				{
					addMesh(&meshes,current);
					current=NULL;//Unlink the mesh that as been added
				}
				current=createMesh();
				if(current==NULL)
				{
					printf("Could not allocate memory for a new mesh");
					//Delete all meshes that have been created in case a new mesh could not be created
					deleteMeshes(&meshes);
					current=NULL;
					break;
				}
			}
			if(strcmp(prefix,"v")==0)
				current->v.size+=3;
			if(strcmp(prefix,"vn")==0)
				current->vn.size+=3;
			if(strcmp(prefix,"vt")==0)
				current->vt.size+=2;
			if(strcmp(prefix,"f")==0)
				current->indices.size+=3;
		}
		//Add last mesh detected
		if(current!=NULL)
		{
			addMesh(&meshes,current);
			current=NULL;
		}

		if(meshes!=NULL)
		{
			//2nd round, read the actual buffer for each mesh;
			fseek(fp,0L,SEEK_SET);
			while(fscanf(fp,"%s",prefix)!=EOF)
			{
				if(strcmp(prefix,"o")==0)
				{
					vPos=0; vnPos=0; vtPos=0; iPos=0;

					//Access to the next mesh
					if(current==NULL)
					{current=meshes;}
					else
					{
						//Before passin to the next mesh set up current mesh
						setUpMesh(&current,imgPath[currentImg]);
						current=current->next;//Access to the next mesh
						currentImg++;
					}

					//Allocate memories for each buffer to the current mesh
					current->v.buffer=(float*)malloc(sizeof(float)*current->v.size);
					current->vt.buffer=(float*)malloc(sizeof(float)*current->vt.size);
					current->vn.buffer=(float*)malloc(sizeof(float)*current->vn.size);
					current->indices.buffer=(unsigned int*)malloc(sizeof(unsigned int)*current->indices.size);
					if(current->v.buffer==NULL||current->vt.buffer==NULL||
							current->vn.buffer==NULL||current->indices.buffer==NULL)
					{
						printf("ERR0R::Could not allocate memory for buffers");
						deleteMeshes(&meshes);
						break;
					}
				}
				if(strcmp(prefix,"v")==0)//Read buffer for vertex positions
				{
					fscanf(fp,"%f %f %f",&x,&y,&z);
					current->v.buffer[vPos]=x;
					current->v.buffer[vPos+1]=y;
					current->v.buffer[vPos+2]=z;
					printf("v %f %f %f\n",current->v.buffer[vPos],current->v.buffer[vPos+1],current->v.buffer[vPos+2]);
					vPos+=3;
				}
				if(strcmp(prefix,"vt")==0)//Read buffer for texture cordinates
				{
					fscanf(fp,"%f %f",&u,&v);
					current->vt.buffer[vtPos]=u;
					current->vt.buffer[vtPos+1]=v;
					printf("vt %f %f\n",current->vt.buffer[vtPos],current->vt.buffer[vtPos+1],current->vt.buffer[vtPos+2]);
					vtPos+=2;
				}
				if(strcmp(prefix,"vn")==0)//Read buffer for vertex normals
				{
					fscanf(fp,"%f %f %f",&x,&y,&z);
					current->vn.buffer[vnPos]=x;
					current->vn.buffer[vnPos+1]=y;
					current->vn.buffer[vnPos+2]=z;
					printf("vn %f %f %f\n",current->vn.buffer[vnPos],current->vn.buffer[vnPos+1],current->vn.buffer[vnPos+2]);
					vnPos+=3;
				}
				if(strcmp(prefix,"f")==0)//Read buffers for indices
				{
					fscanf(fp,"%d/%*d/%*d %d/%*d/%*d %d/%*d/%*d",&index[0], &index[3], &index[6]);
					current->indices.buffer[iPos]= index[0] - 1; //first vertex index
					current->indices.buffer[iPos+1]= index[3] - 1;
					current->indices.buffer[iPos+2]= index[6] - 1;
					printf("f %d %d %d\n",current->indices.buffer[iPos]+1,current->indices.buffer[iPos+1]+1,current->indices.buffer[iPos+2]+1);
					iPos+=3;
				}
			}
			//Set up last mesh that was detected
			setUpMesh(&current,imgPath[currentImg]);
			current = NULL;
		}
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

void setUpMesh(MESHBUFFER** mesh,char* imgPath)
{
	MESHBUFFER* m = *mesh;
	//Generate VAOS and buffer
	glGenVertexArrays(1,&m->VAO); //Generate vertex Array
	glBindVertexArray(m->VAO);//Bind Vertex array
	//GEN VBO of vertex and link it to the vao
	glGenBuffers(1,&m->VBO[0]);
	glBindBuffer(GL_ARRAY_BUFFER,m->VBO[0]);
	glBufferData(GL_ARRAY_BUFFER,m->v.size*sizeof(float),m->v.buffer,GL_STATIC_DRAW);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
	glEnableVertexAttribArray(0);

	//GEN VBO of vertex texture and link it to the vao
	glGenBuffers(1,&m->VBO[1]);
	glBindBuffer(GL_ARRAY_BUFFER,m->VBO[1]);
	glBufferData(GL_ARRAY_BUFFER,m->vt.size*sizeof(float),m->vt.buffer,GL_STATIC_DRAW);
	glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,2*sizeof(float),(void*)0);
	glEnableVertexAttribArray(1);
	
	//GEN VBO of vertex normal and link it to the vao
	glGenBuffers(1,&m->VBO[2]);
	glBindBuffer(GL_ARRAY_BUFFER,m->VBO[2]);
	glBufferData(GL_ARRAY_BUFFER,m->vn.size*sizeof(float),m->vn.buffer,GL_STATIC_DRAW);
	glVertexAttribPointer(2,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
	glEnableVertexAttribArray(2);

	//loadTexture
	m->texLoaded = loadTexture(imgPath,&m->texture);

	//Gen EBO
	glGenBuffers(1,&m->EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,m->indices.size*sizeof(unsigned int),m->indices.buffer,GL_STATIC_DRAW);

	//Unbind so it wont be modified by other vaos
	glBindVertexArray(0);

	m->glEnabled = true;
}

void drawMeshes(MESHBUFFER* meshes,shaderProgram* p)
{
	MESHBUFFER* m = meshes;
	while(m!=NULL)
	{
		//Bind to current MESH VAO
		//Draw current mesh
		glUseProgram(*p);
		glBindVertexArray(m->VAO);
		glActiveTexture(GL_TEXTURE0); //currently only handles one simple texture per mesh
		glUniform1i(glGetUniformLocation(*p,"texture1"),0);
		glBindTexture(GL_TEXTURE_2D,m->texture);
		glDrawElements(GL_TRIANGLES,m->indices.size,GL_UNSIGNED_INT,0);//DRAW THE DATA
		glBindVertexArray(0); //UNBIND THE VAO
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
		printf("Image found!!\n");
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,data);
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
		mb += 0.000001f * (sizeof(current->v.buffer)+sizeof(current->vt.buffer)+sizeof(current->vn.buffer)+sizeof(current->indices.buffer));
		current=current->next;
	}
	return mb;
}

