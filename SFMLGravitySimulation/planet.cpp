#include "planet.h"

Planet::Planet(float mass, float radius, sf::Vector2f startPosition, sf::Vector2f startDirection, sf::Color color)
{
	this->mass = mass;
	this->radius = radius;
	this->color = color;
	this->velocity = startDirection;

	shape.setRadius(radius);
	shape.setFillColor(color);
	shape.setPosition(startPosition - sf::Vector2f(1.0f, 1.0f) * radius);
}

void Planet::DrawPlanets(std::vector<Planet>& planets, sf::RenderWindow& window)
{
	for (int i = 0; i < planets.size(); i++)
	{
		planets[i].shape.move(planets[i].velocity);
		window.draw(planets[i].shape);
	}
}

sf::RectangleShape Planet::DrawStartVector(float startX, float startY, sf::Vector2f startVelocity, float y2)
{
	float x = startVelocity.x;
	float y = startVelocity.y;
	float lineThickness = 5.0f;
	float length = sqrt(pow(x, 2) + pow(y, 2));
	x > 0 ? length *= 1 : length *= -1;
	sf::Vector2f lineVector(length, lineThickness);
	sf::RectangleShape line(lineVector);
	line.setFillColor(sf::Color::White);
	line.setPosition(sf::Vector2f(startX, startY));
	line.rotate(atan(y / x) * 180 / 3.14f);
	return line;
}

void Planet::CollisionCheck(std::vector<Planet>& planets, const int WINDOW_WIDTH, const int WINDOW_HEIGHT)
{
	for (int i = 0; i < planets.size(); i++)
	{
		if (planets[i].shape.getPosition().x <= 0 || planets[i].shape.getPosition().x >= WINDOW_WIDTH - planets[i].radius * 2)
			planets[i].velocity.x *= -1;
		if (planets[i].shape.getPosition().y <= 0 || planets[i].shape.getPosition().y >= WINDOW_HEIGHT - planets[i].radius * 2)
			planets[i].velocity.y *= -1;
	}

	if (planets.size() > 1)
		for (int i = 0; i < planets.size() - 1; i++)
		{
			for (int j = i + 1; j < planets.size(); j++)
			{
				if (GetDistation(planets[i], planets[j]) <= (planets[i].GetRadius() + planets[j].GetRadius()))
				{
					sf::Vector2f v1 = planets[i].velocity;
					sf::Vector2f v2 = planets[j].velocity;

					sf::Vector2f deltaV = v1 - v2;

					float m1 = planets[i].mass;
					float m2 = planets[j].mass;

					sf::Vector2f c1 = planets[i].shape.getPosition();
					sf::Vector2f c2 = planets[j].shape.getPosition();

					sf::Vector2f deltaC = c1 - c2;
					float moduleDeltaC = sqrt(deltaC.x * deltaC.x + deltaC.y * deltaC.y);

					float scalarProduct = deltaV.x * deltaC.x + deltaV.y * deltaC.y;

					planets[i].velocity = v1 - (2 * m2 * scalarProduct * deltaC) / ((m1 + m2) * moduleDeltaC * moduleDeltaC);

					deltaV *= -1.0f;
					deltaC *= -1.0f;

					moduleDeltaC = sqrt(deltaC.x * deltaC.x + deltaC.y * deltaC.y);
					scalarProduct = deltaV.x * deltaC.x + deltaV.y * deltaC.y;

					planets[j].velocity = v2 - (2 * m1 * scalarProduct * deltaC) / ((m1 + m2) * moduleDeltaC * moduleDeltaC);
				}
				else
					CalculateForces(planets);
			}
		}
}

void Planet::CalculateForces(std::vector<Planet>& planets)
{
	if (planets.size() > 1)
		for (int i = 0; i < planets.size() - 1; i++)
		{
			for (int j = i + 1; j < planets.size(); j++)
			{
				float x = planets[j].shape.getPosition().x + planets[j].GetRadius() - planets[i].shape.getPosition().x - planets[i].GetRadius();
				float y = planets[j].shape.getPosition().y + planets[j].GetRadius() - planets[i].shape.getPosition().y - planets[i].GetRadius();
				float lenght = GetDistation(planets[i], planets[j]);
				sf::Vector2f force(x / lenght, y / lenght);
				force *= (float)(planets[i].GetMass() * planets[j].GetMass() / pow(lenght, 2));
				planets[i].velocity += force;
				planets[j].velocity -= force;
			}
		}
}

void Planet::ClampStartVelocity(sf::Vector2f& startVelocity, float maxVelocity)
{
	float x = startVelocity.x;
	float y = startVelocity.y;
	float lenght = sqrt(pow(x, 2) + pow(y, 2));
	if (lenght > maxVelocity)
	{
		startVelocity.x = (x) / lenght * maxVelocity;
		startVelocity.y = (y) / lenght * maxVelocity;
	}
}

void Planet::SetVelocity(sf::Vector2f velocity)
{
	this->velocity = velocity;
}

sf::Vector2f Planet::GetVelocity()
{
	return velocity;
}

float Planet::GetDistation(Planet planet1, Planet planet2)
{
	float x = planet2.shape.getPosition().x + planet2.GetRadius() - planet1.shape.getPosition().x - planet1.GetRadius();
	float y = planet2.shape.getPosition().y + planet2.GetRadius() - planet1.shape.getPosition().y - planet1.GetRadius();
	return sqrt(pow(x, 2) + pow(y, 2));
}

float Planet::GetMass()
{
	return mass;
}

float Planet::GetRadius()
{
	return radius;
}
