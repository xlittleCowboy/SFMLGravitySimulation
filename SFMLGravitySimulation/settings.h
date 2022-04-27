#pragma once

#include <SFML/Graphics.hpp>

class Settings
{
private:
	static float deltaTime;
	static sf::Clock clock;

public:
	static float GetDeltaTime();
	static void UpdateDeltaTime();
};