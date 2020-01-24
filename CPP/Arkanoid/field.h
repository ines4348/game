#pragma once
#include <SFML/Graphics.hpp>

enum struct BrickCategory
{
    BRICK,
    STRONG_BRICK,
    NONE,
};

struct Brick
{
    BrickCategory category;
    sf::RectangleShape shape;
};

struct Field
{
    size_t width = 0;
    size_t height = 0;
    size_t countBricks = 0;
    Brick* bricks = nullptr;
};

void initializeField(Field& field);
void drawField(sf::RenderWindow& window, const Field& field);
void destroyBrick(Field& field, size_t indexBrick);
void destroyField(Field& field);