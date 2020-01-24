#include "ball.h"
#include "racket.h"
#include "field.h"
#include <iostream>

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;

// Скорость движения шара.
sf::Vector2f BALL_SPEED = { 300.f, 45.f };

// Радиус шара в пикселях.
constexpr float BALL_RADIUS = 20.f;

// Размер ракетки шара в пикселях.
static const sf::Vector2f RACKET_SIZE = { 120, 20 };

// RGB-цвет заливки шара/
const sf::Color BALL_COLOR = sf::Color(255, 216, 0);


// Начальная позиция шара в пикселях.
static const sf::Vector2f BALL_INITIAL_POSITION = {450, 500 };

void initializeBall(Ball& ball)
{
    ball.shape.setRadius(BALL_RADIUS);
    ball.shape.setFillColor(BALL_COLOR);
    ball.shape.setPosition(BALL_INITIAL_POSITION);
}

void updateBall(Ball& ball, Racket& racket, float elapsedTime, Field& field)
{
    sf::Vector2f positionBall = ball.shape.getPosition();
    positionBall += BALL_SPEED * elapsedTime;

    collisionBallWall(ball);
    collisionBallRacket(ball, racket);
    collisionBallBricks(ball, field);

    ball.shape.setPosition(positionBall);
}

void collisionBallWall(Ball& ball)
{
    sf::Vector2f positionBall = ball.shape.getPosition();

    if ((positionBall.x + 2 * BALL_RADIUS >= WINDOW_WIDTH) && (BALL_SPEED.x > 0))
    {
        BALL_SPEED.x = -BALL_SPEED.x;
    }
    if ((positionBall.x < 0) && (BALL_SPEED.x < 0))
    {
        BALL_SPEED.x = -BALL_SPEED.x;
    }
    if ((positionBall.y + 2 * BALL_RADIUS >= WINDOW_HEIGHT) && (BALL_SPEED.y > 0))
    {
        BALL_SPEED.y = -BALL_SPEED.y;
    }
    if ((positionBall.y < 0) && (BALL_SPEED.y < 0))
    {
        BALL_SPEED.y = -BALL_SPEED.y;
    }
}

void collisionBallRacket(Ball& ball, Racket& racket)
{
    sf::Vector2f positionBall = ball.shape.getPosition();
    sf::Vector2f positionRacket = racket.shape.getPosition();
    
    if ((positionBall.x >= positionRacket.x) && (positionBall.x <= positionRacket.x + RACKET_SIZE.x) && (positionBall.y + BALL_RADIUS >= positionRacket.y - RACKET_SIZE.y) && (BALL_SPEED.y > 0))
    {
        BALL_SPEED.y = -BALL_SPEED.y;
    }
}

void collisionBallBricks(Ball& ball, Field& field)
{
    for (size_t i = 0; i < field.countBricks; i++)
    {
        Brick brick;
        brick = field.bricks[i];
        collisionBallBrick(ball, brick, field, i);
    }
}

void collisionBallBrick(Ball& ball, Brick& brick, Field& field, size_t i)
{
    sf::Vector2f positionBall = ball.shape.getPosition();
    sf::Vector2f positionBrick = brick.shape.getPosition();
    sf::Vector2f sizeBrick = brick.shape.getSize();

    if (((positionBall.x + 2 * BALL_RADIUS) >= positionBrick.x) && (positionBall.x < positionBrick.x) && ((positionBall.y + BALL_RADIUS) >= positionBrick.y) && ((positionBall.y + BALL_RADIUS) <= (positionBrick.y + brick.shape.getSize().y)) && (BALL_SPEED.x > 0))
    {
        destroyBrick(field, i);
        BALL_SPEED.x = -BALL_SPEED.x;
    }
    if ((positionBall.x <= (positionBrick.x + sizeBrick.x)) && ((positionBall.y + BALL_RADIUS) >= positionBrick.y) && ((positionBall.y + BALL_RADIUS) <= (positionBrick.y + sizeBrick.y)) && (BALL_SPEED.x < 0))
    {
        destroyBrick(field, i);
        BALL_SPEED.x = -BALL_SPEED.x;
    }
    if((positionBall.x + BALL_RADIUS >= positionBrick.x) && ((positionBall.x + BALL_RADIUS) <= (positionBrick.x + sizeBrick.x)) && (positionBall.y + 2 * BALL_RADIUS >= positionBrick.y) && ((positionBall.y + BALL_RADIUS) < positionBrick.y) && (BALL_SPEED.y > 0))
    {
        destroyBrick(field, i);
        BALL_SPEED.y = -BALL_SPEED.y;
    }
    if ((positionBall.x + BALL_RADIUS >= positionBrick.x) && ((positionBall.x + BALL_RADIUS) <= (positionBrick.x + sizeBrick.x)) && (positionBall.y <= positionBrick.y + sizeBrick.y) && (BALL_SPEED.y < 0))
    {
        destroyBrick(field, i);
        BALL_SPEED.y = -BALL_SPEED.y;
    }
}
