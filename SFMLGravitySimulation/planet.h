#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "settings.h"

class Planet
{
private:
	float mass, radius;
	sf::CircleShape shape;
	sf::Color color;
	sf::Vector2f velocity;

	static std::vector<Planet> planets;

	static float GetDistation(Planet planet1, Planet planet2);
	static void CalculateForces();

public:
	Planet(float mass, float radius, sf::Vector2f startPosition, sf::Vector2f startDirection, sf::Color color);

	static void AddPlanet(Planet planet);

	static void CollisionCheck(const int WINDOW_WIDTH, const int WINDOW_HEIGHT);
	static void DrawPlanets(sf::RenderWindow& window);
	static sf::RectangleShape DrawStartVector(float startX, float startY, sf::Vector2f startVelocity, float y2);

	sf::Vector2f GetVelocity();
	float GetMass();
	float GetRadius();
};

