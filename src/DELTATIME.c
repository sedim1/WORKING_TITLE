#include "DELTATIME.h"

void countTime(DELTATIME* dT)
{
	dT->currentTime = glfwGetTime();
}

void saveLastTime(DELTATIME* dT)
{
	dT->lastTime=dT->currentTime;
}

void updateDeltaTime(DELTATIME* dT)
{
	dT->delta = dT->currentTime - dT->lastTime;
}
