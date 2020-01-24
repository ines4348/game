#pragma once

#include <SFML/Graphics.hpp>

// ����������� �������� ������� (�� ��������, �����, ������)
enum struct Direction
{
    NONE,
    LEFT,
    RIGHT
};

// ��������� ��������� �������
// ������� ����� ������������� ������� � ������������ ��������.
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