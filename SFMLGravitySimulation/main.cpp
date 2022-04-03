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
    float startRadius = 10, startMass = 8;
    bool isButtonPressed = false;

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
                    startRadius += 0.25f;
                    startMass += 0.01f;
                }
                if (event.mouseWheel.delta -= 1)
                {
                    startRadius -= 0.25f;
                    startMass -= 0.01f;
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
                    sf::Color randomColor(rand() % 255, rand() % 255, rand() % 255);
                    Planet planet(pow(startMass, 8), startRadius, startPosition, startDirection / 25.0f, randomColor);

                    planets.push_back(planet);
                    isButtonPressed = false;
                }
            }
        }

        window.clear();
        Planet::DrawPlanets(planets, window);
        Planet::CollisionCheck(planets, WINDOW_WIDTH, WINDOW_HEIGHT);
        Planet::CalculateForces(planets);
        sf::CircleShape templateShape;
        templateShape.setFillColor(sf::Color::Green);
        templateShape.setRadius(startRadius);
        window.draw(templateShape);
        window.display();
    }

    return 0;
}