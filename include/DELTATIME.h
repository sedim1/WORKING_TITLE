#ifndef DELTATIME_H
#define DELTATIME_H

#include <GLFW/glfw3.h>

typedef struct{
	double currentTime;
	double lastTime;
	double delta;
}DELTATIME; //USED FOR USING DELTATIME GLOBALLY OR LOCALLY

void countTime(DELTATIME* dT);
void saveLastTime(DELTATIME* dT);
void updateDeltaTime(DELTATIME *dT); //CALCULATES DELTATIME IN SECONDS

#endif
