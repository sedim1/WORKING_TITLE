#ifndef STRARRAY_H
#define STRARRAY_H

#include<string.h>
#include<stdlib.h>

typedef struct{
	char** strings;
	int size;
}STR_ARRAY;

void addString(STR_ARRAY* array,char* str);
void eraseStrings(STR_ARRAY* array);

#endif
