#include "DELTATIME.h"

void startTime(DELTATIME* dT)
{
	dT->timeStart = glfwGetTime();
}

void startEnd(DELTATIME* dT)
{
	dT->timeEnd = glfwGetTime();
}

void calculateDeltatime(DELTATIME* dT)
{
	dT->delta = dT->timeEnd - dT->timeStart;
}
