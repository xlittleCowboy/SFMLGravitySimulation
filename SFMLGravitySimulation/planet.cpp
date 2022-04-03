#include "planet.h"

Planet::Planet(float mass, float radius, sf::Vector2f startPosition, sf::Vector2f startDirection, sf::Color color)
{
	this->mass = mass;
	this->radius = radius;
	this->color = color;
	this->startDirection = startDirection;

	shape.setRadius(radius);
	shape.setFillColor(color);
	shape.setPosition(startPosition - sf::Vector2f(1.0f, 1.0f) * radius);
}

void Planet::DrawPlanets(std::vector<Planet>& planets, sf::RenderWindow& window)
{
	for (int i = 0; i < planets.size(); i++)
	{
		planets[i].shape.move(planets[i].startDirection);
		window.draw(planets[i].shape);
	}
}

void Planet::CollisionCheck(std::vector<Planet>& planets, const int WINDOW_WIDTH, const int WINDOW_HEIGHT)
{
	for (int i = 0; i < planets.size(); i++)
	{
		if (planets[i].shape.getPosition().x <= 0 || planets[i].shape.getPosition().x >= WINDOW_WIDTH - planets[i].radius * 2)
			planets[i].startDirection.x *= -1;
		if (planets[i].shape.getPosition().y <= 0 || planets[i].shape.getPosition().y >= WINDOW_HEIGHT - planets[i].radius * 2)
			planets[i].startDirection.y *= -1;
	}
}

void Planet::CalculateForces(std::vector<Planet>& planets)
{
	if (planets.size() > 1)
	{
		for (int i = 0; i < planets.size() - 1; i++)
		{
			float x = planets[i + 1].shape.getPosition().x - planets[i].shape.getPosition().x;
			float y = planets[i + 1].shape.getPosition().y - planets[i].shape.getPosition().y;
			float lenght = sqrt(pow(x, 2) + pow(y, 2));
			sf::Vector2f forceDirection(x / lenght, y / lenght);
			forceDirection *= (float)(6.67408 * pow(10, -11) * planets[i].GetMass() * planets[i + 1].GetMass() / pow(lenght + planets[i].radius + planets[i + 1].radius, 2));
			planets[i].startDirection += forceDirection;
			planets[i + 1].startDirection -= forceDirection;
		}
	}
}

float Planet::GetMass()
{
	return mass;
}
