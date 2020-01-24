#include "field.h"
#include "ball.h"
#include "racket.h"
#include <SFML/Graphics.hpp>
#include <iostream>

// -- объявления констант --
constexpr unsigned ANTIALIASING_LEVEL = 8;
constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;
constexpr unsigned MAX_FPS = 60;

// Функция создаёт окно приложения.
void createWindow(sf::RenderWindow& window)
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = ANTIALIASING_LEVEL;
    window.create(
        sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
        "Android Game Clone", sf::Style::Default, settings);
    window.setFramerateLimit(MAX_FPS);
}

// Функция обрабатывает все события, скопившиеся в очереди событий SFML.
void handleEvents(sf::RenderWindow& window, Racket& racket)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }

        // Клавиши управления ракеткой
        else if (event.type == sf::Event::KeyPressed)
        {
            handleRacketKeyPress(event.key, racket);
        }
        else if (event.type == sf::Event::KeyReleased)
        {
            handleRacketKeyRelease(event.key, racket);
        }
    }
}

// Функция обновляет фигуры шара и ракетки.
void update(sf::Clock& clock, Ball& ball, Racket& racket, Field& field)
{
    const float elapsedTime = clock.getElapsedTime().asSeconds();
    clock.restart();
    updateRacket(racket, elapsedTime);
    updateBall(ball, racket, elapsedTime, field);
}

// Функция рисует фигуры шара и ракетки.
void render(sf::RenderWindow& window, Ball& ball, const Racket& racket, const Field& field)
{
    window.clear();
    drawField(window, field);
    window.draw(ball.shape);
    window.draw(racket.shape);
    window.display();
}

int main(int, char* [])
{
    sf::RenderWindow window;
    createWindow(window);

    Field field;
    initializeField(field);
    Ball ball;
    initializeBall(ball);
    Racket racket;
    initializeRacket(racket);

    sf::Clock clock;
    while (window.isOpen())
    {
        handleEvents(window, racket);
        update(clock, ball, racket, field);
        render(window, ball, racket, field);
    }

    return 0;
}