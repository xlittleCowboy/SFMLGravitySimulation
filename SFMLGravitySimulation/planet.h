#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class Planet
{
private:
	float mass, radius;
	sf::CircleShape shape;
	sf::Color color;
	sf::Vector2f startDirection;


public:
	Planet(float mass, float radius, sf::Vector2f startPosition, sf::Vector2f startDirection, sf::Color color);

	static void DrawPlanets(std::vector<Planet>& planets, sf::RenderWindow& window);
	static void CollisionCheck(std::vector<Planet>& planets, const int WINDOW_WIDTH, const int WINDOW_HEIGHT);
	static void CalculateForces(std::vector<Planet>& planets);

	float GetMass();
};

