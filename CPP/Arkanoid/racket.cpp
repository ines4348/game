#include "racket.h"
#include "field.h"
#include <iostream>

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;

// Скорость движения ракетки, пикселей в секунду.
constexpr float RACKET_SPEED = 320.f;

// Размер ракетки шара в пикселях.
static const sf::Vector2f RACKET_SIZE = {120, 20};

// RGB-цвет заливки ракетки/
const sf::Color RACKET_COLOR = sf::Color(0, 216, 0);

// Начальная позиция ракетки в пикселях.
static const sf::Vector2f RACKET_INITIAL_POSITION = {100, 560};

void initializeRacket(Racket& racket)
{
    racket.directionRacket = Direction::NONE;
    racket.shape.setSize(RACKET_SIZE);
    racket.shape.setFillColor(RACKET_COLOR);
    racket.shape.setPosition(RACKET_INITIAL_POSITION);
}

void updateRacket(Racket& racket, float elapsedTime)
{
    const float step = RACKET_SPEED * elapsedTime;
    sf::Vector2f position = racket.shape.getPosition();

    switch(racket.directionRacket)
    {
    case Direction::LEFT:
        position.x -= step;
        break;
    case Direction::RIGHT:
        position.x += step;
        break;
    case Direction::NONE:
        break;
    }    
    
    if (!isCollisionRacketWall(position))
    {
        racket.shape.setPosition(position);
    }
}

bool isCollisionRacketWall(sf::Vector2f position)
{
    bool isCollision = false;
    if ((position.x <= 0) || (position.x + RACKET_SIZE.x >= WINDOW_WIDTH))
    {
        isCollision = true;
    }
    return isCollision;
}

bool handleRacketKeyPress(const sf::Event::KeyEvent& event, Racket& racket)
{
    bool handled = true;
    switch(event.code)
    {
    case sf::Keyboard::Left:
        racket.directionRacket = Direction::LEFT;
        break;
    case sf::Keyboard::Right:
        racket.directionRacket = Direction::RIGHT;
        break;
    default:
        handled = false;
        break;
    }
    return handled;
}

bool handleRacketKeyRelease(const sf::Event::KeyEvent& event, Racket& racket)
{
    bool handled = true;
    switch(event.code)
    {
    case sf::Keyboard::Left:
        if(racket.directionRacket == Direction::LEFT)
        {
            racket.directionRacket = Direction::NONE;
        }
        break;
    case sf::Keyboard::Right:
        if(racket.directionRacket == Direction::RIGHT)
        {
            racket.directionRacket = Direction::NONE;
        }
        break;
    default:
        handled = false;
        break;
    }

    return handled;
}