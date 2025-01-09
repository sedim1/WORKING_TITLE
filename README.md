### WORKING TITLE
Aqui encontraran algo de la documentacion del projecto


#####LECTOR DE SHADERS

El lector de shader nos crea y compila shader en una sola linea usando la siguiente funcion:

**shaderProgram createShaderProgram(char *shadersSources[],GLenum types[],int n)**

**shaderSources: ** son las ubicaciones de los codigos de cada shader que componen al programa de shader

**types**: tipo de shader respectivamente a cada codigo del shader

**n**: numeros de shaders que componen al programa en total

#####LECTOR DE OBJ
En el lector de obj actualmente solo soporta modelos donde sus caras son **trianglulos**, si intentas cargar un obj donde las caras sean cuadrados o poligonos el programa tendra un error y detendra su ejecucion.

Tambien por el momento todos los objetos que componen los modelos 3d solo soportan una textura por objeto.

**Cargando Modelos 3D**
Al cargar un modelo 3d la funcion esperara 2 argumentos

**MESHBUFFER* loadMeshes(archivo.obj,texturas)**
- archivo.obj: Ubicacion del archivo obj
- texturas: arreglo de strings en donde indicaras la textura que se le asignara a cada  objeto del mesh respectivamente (tomar en cuenta el orden de los objetos que componen al modelo 3D)
 - **NOTA: se pasa de la siguiente manera:**  
 - char** texturas[N] = {tex1.png,tex2.png,...,texn.png};


