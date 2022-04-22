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
	sf::Vector2f velocity;

	static float GetDistation(Planet planet1, Planet planet2);
	static void CalculateForces(std::vector<Planet>& planets);

public:
	Planet(float mass, float radius, sf::Vector2f startPosition, sf::Vector2f startDirection, sf::Color color);

	static void DrawPlanets(std::vector<Planet>& planets, sf::RenderWindow& window);
	static void CollisionCheck(std::vector<Planet>& planets, const int WINDOW_WIDTH, const int WINDOW_HEIGHT);
	static void ClampStartVelocity(sf::Vector2f& startVelocity, float maxVelocity);
	static sf::RectangleShape DrawStartVector(float startX, float startY, sf::Vector2f startVelocity, float y2);

	float GetMass();
	float GetRadius();
	sf::Vector2f GetVelocity();
	void SetVelocity(sf::Vector2f velocity);
};

