#pragma once

#include <SFML/Graphics.hpp>

struct Field;
struct Racket;
struct Brick;

// Структура описывает шар
// Шар можно смоделировать фигурой.
struct Ball
{
    sf::CircleShape shape;
};

void initializeBall(Ball& ball);
void updateBall(Ball& ball, Racket& racket, float elapsedTime, Field& field);
void collisionBallWall(Ball& ball);
void collisionBallRacket(Ball& ball, Racket& racket);
void collisionBallBricks(Ball& ball, Field& field);
void collisionBallBrick(Ball& ball, Brick& brick, Field& field, size_t i);