#include"STRARRAY.h"

void addString(STR_ARRAY* array, char* str)
{
    char** temp;
    array->size++;
    if (array->size == 1)
        array->strings = (char**)malloc(sizeof(char*) * array->size);
    else
    {
        temp = realloc(array->strings, sizeof(char*) * array->size);
        if (temp == NULL) {
            // Handle memory allocation failure
            return;
        }
        array->strings = temp;
    }
    int length = strlen(str) + 1; // Include space for the null terminator
    array->strings[array->size - 1] = (char*)malloc(sizeof(char) * length);
    if (array->strings[array->size - 1] != NULL) {
        strncpy(array->strings[array->size - 1], str, length);
    }
}

void eraseStrings(STR_ARRAY* array)
{
    for (int i = 0; i < array->size; i++)
        free(array->strings[i]);
    free(array->strings);
    array->strings = NULL; // Avoid dangling pointer
    array->size = 0;       // Reset the size
}
