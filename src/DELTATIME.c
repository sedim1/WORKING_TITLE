#include "DELTATIME.h"

void startTime(DELTATIME* dT)
{
	dT->timeStart = glfwGetTime();
}

void endTime(DELTATIME* dT)
{
	dT->timeEnd = glfwGetTime();
}

void calculateDeltaTime(DELTATIME* dT)
{
	dT->delta = dT->timeEnd - dT->timeStart;
}
