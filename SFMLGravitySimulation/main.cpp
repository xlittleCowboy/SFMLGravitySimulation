#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <ctime>

#include "planet.h"

int main()
{
    srand(time(0));

    const int WINDOW_WIDTH = sf::VideoMode().getDesktopMode().width, WINDOW_HEIGHT = sf::VideoMode().getDesktopMode().height;
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Gravity!", sf::Style::Fullscreen);
    window.setVerticalSyncEnabled(true);

    std::vector<Planet> planets;

    float startX = 0, startY = 0;
    float radius = 10, mass = 10;

    float radiusIncreaser = 1.0f;
    float massIncreaser = 1.0f;

    float maxRadius = 75.0f;
    float maxMass = 75.0f;

    bool isButtonPressed = false;

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
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left && !isButtonPressed)
                {
                    startX = event.mouseButton.x;
                    startY = event.mouseButton.y;
                    isButtonPressed = true;
                }
            }
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
                    float x = sf::Mouse::getPosition(window).x;
                    float y = sf::Mouse::getPosition(window).y;
                    sf::Vector2f startPosition(x, y);

                    sf::Vector2f startDirection(x - startX, y - startY);

                    isBlue ? col = blue : col = yellow;
                    isBlue = !isBlue;

                    Planet planet(mass, radius, startPosition, startDirection / 25.0f, col);

                    planets.push_back(planet);
                    isButtonPressed = false;
                }
            }
        }

        window.clear();
        Planet::DrawPlanets(planets, window);
        Planet::CollisionCheck(planets, WINDOW_WIDTH, WINDOW_HEIGHT);
        //Planet::CheckVelocity(planets, 25.0f);
        sf::CircleShape templateShape;
        templateShape.setFillColor(col);
        templateShape.setRadius(radius);
        window.draw(templateShape);
        window.display();
    }

    return 0;
}