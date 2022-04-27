#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <ctime>

#include "planet.h"
#include "settings.h"

// Initialize static values
float Settings::deltaTime;
sf::Clock Settings::clock;

std::vector<Planet> Planet::planets;

int main()
{
    const int WINDOW_WIDTH = sf::VideoMode().getDesktopMode().width, WINDOW_HEIGHT = sf::VideoMode().getDesktopMode().height;
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Gravity!", sf::Style::Fullscreen);
    window.setVerticalSyncEnabled(true);

    float startX = 0, startY = 0;
    float x = 0, y = 0;
    sf::Vector2f startVelocity;
    float radius = 10, mass = 10;

    float radiusIncreaser = 1.0f;
    float massIncreaser = 1.0f;

    float maxRadius = 75.0f;
    float maxMass = 75.0f;

    bool isLeftButtonPressed = false;

    sf::Color blue = sf::Color::Blue;
    sf::Color yellow = sf::Color::Yellow;
    sf::Color col = blue;
    bool isBlue = true;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();

            if (event.type == sf::Event::MouseWheelMoved)
            {
                if (event.mouseWheel.delta == 1)
                {
                    if (radius < maxRadius)
                        radius += radiusIncreaser;

                    if (mass < maxMass)
                        mass += massIncreaser;
                }
                if (event.mouseWheel.delta -= 1)
                {
                    if (radius > 0)
                        radius -= radiusIncreaser;

                    if (mass > 0)
                        mass -= massIncreaser;
                }
            }
            if (event.type == sf::Event::MouseButtonReleased)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    isLeftButtonPressed = false;

                    sf::Vector2f startPosition(startX, startY);

                    isBlue ? col = blue : col = yellow;
                    isBlue = !isBlue;

                    Planet planet(mass, radius, startPosition, startVelocity, col);

                    Planet::AddPlanet(planet);
                }
            }
        }

        window.clear();
        Planet::DrawPlanets(window);
        Planet::CollisionCheck(WINDOW_WIDTH, WINDOW_HEIGHT);

        sf::CircleShape templateShape;
        templateShape.setFillColor(col);
        templateShape.setRadius(radius);
        window.draw(templateShape);

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if (!isLeftButtonPressed)
            {
                startX = sf::Mouse::getPosition(window).x;
                startY = sf::Mouse::getPosition(window).y;
                isLeftButtonPressed = true;
            }

            x = sf::Mouse::getPosition(window).x;
            y = sf::Mouse::getPosition(window).y;
            startVelocity.x = x - startX;
            startVelocity.y = y - startY;
            window.draw(Planet::DrawStartVector(startX, startY, startVelocity, y));
        }

        window.display();

        Settings::UpdateDeltaTime();
    }

    return 0;
}