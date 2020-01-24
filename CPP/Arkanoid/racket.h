#pragma once

#include <SFML/Graphics.hpp>

// Ќаправление движени€ ракетки (не движетс€, влево, вправо)
enum struct Direction
{
    NONE,
    LEFT,
    RIGHT
};

// —труктура описывает ракетку
// –акетку можно смоделировать фигурой и направлением движени€.
struct Racket
{
    sf::RectangleShape shape;
    Direction directionRacket;
};

void initializeRacket(Racket& racket);
void updateRacket(Racket& racket, float elapsedTime);
bool isCollisionRacketWall(sf::Vector2f position);
bool handleRacketKeyPress(const sf::Event::KeyEvent& event, Racket& racket);
bool handleRacketKeyRelease(const sf::Event::KeyEvent& event, Racket& racket);