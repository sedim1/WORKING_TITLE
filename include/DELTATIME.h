#ifndef DELTATIME_H
#define DELTATIME_H

#include <GLFW/glfw3.h>

typedef struct{
	double timeStart;
	double timeEnd;
	double delta;
}DELTATIME; //USED FOR USING DELTATIME GLOBALLY OR LOCALLY

void startTime(DELTATIME* dT); //SETS TIME STARTS IN SECONDS
void endTime(DELTATIME *dT); //SETS TIME END IN SECONDS
void calculateDeltaTime(DELTATIME *dT); //CALCULATES DELTATIME IN SECONDS

#endif
