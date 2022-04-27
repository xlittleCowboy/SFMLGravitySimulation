#include "settings.h"

float Settings::GetDeltaTime()
{
	return deltaTime;
}

void Settings::UpdateDeltaTime()
{
	deltaTime = clock.getElapsedTime().asSeconds();
	clock.restart();
}
