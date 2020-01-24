#include "field.h"

static const float BRICK_WIDTH = 25.f;
static const float BRICK_HEIGHT = 25.f;
static const size_t FIELD_WIDTH = 32;
static const size_t FIELD_HEIGHT = 24;
static const char FIELD_MAZE[] = "                                "
                                 "                                "
                                 "                                "
                                 "                                "
                                 "                                "
                                 "                                "
"   222      1111121111111       "
"                                "
"                                "
"                                "
"                                "
"                                "
"                                "
"                                "
"                                "
"                                "
"                                "
"                                "
"                                "
"                                "
"                                "
"                                "
"                                "
"                                ";

static const sf::Color BRICK_COLOR = sf::Color(0xCC, 0x66, 0x00);
static const sf::Color FIELD_COLOR = sf::Color(00, 00, 33);
static const sf::Color WALL_COLOR = sf::Color(40, 40, 40);

static sf::FloatRect moveRect(const sf::FloatRect& rect, sf::Vector2f& offset)
{
    return { rect.left + offset.x, rect.top + offset.y, rect.width, rect.height };
}

void initializeField(Field& field)
{
    field.width = FIELD_WIDTH;
    field.height = FIELD_HEIGHT;
    field.bricks = new Brick[field.width * field.height];
    size_t indexBrick = 0;
    for (size_t y = 0; y < field.height; y++)
    {
        for (size_t x = 0; x < field.width; x++)
        {
            bool isAddBrick = false;
            const size_t offset = x + y * field.width;
            BrickCategory category;
            sf::Color color;
            if (FIELD_MAZE[offset] == '1')
            {
                category = BrickCategory::BRICK;
                color = WALL_COLOR;
                isAddBrick = true;
            }
            else if(FIELD_MAZE[offset] == '2')
            {
                category = BrickCategory::STRONG_BRICK;
                color = BRICK_COLOR;
                isAddBrick = true;
            }
            if (isAddBrick)
            {
                Brick& brick = field.bricks[indexBrick];
                brick.category = category;
                brick.shape.setPosition(x * BRICK_WIDTH, y * BRICK_HEIGHT);
                brick.shape.setSize(sf::Vector2f(BRICK_WIDTH, BRICK_HEIGHT));
                brick.shape.setFillColor(color);
                indexBrick++;
            }
            
        }
    }
    field.countBricks = indexBrick;
}

void drawField(sf::RenderWindow& window, const Field& field)
{
    for (size_t i = 0; i < field.countBricks; i++)
    {
        window.draw(field.bricks[i].shape);
    }
}

void destroyBrick(Field& field, size_t indexBrick)
{
    
    if(field.bricks[indexBrick].category == BrickCategory::STRONG_BRICK)
    {
        field.bricks[indexBrick].category = BrickCategory::BRICK;
        field.bricks[indexBrick].shape.setFillColor(WALL_COLOR);
    }
    else
    {
        for (size_t i = indexBrick; i < field.countBricks; ++i)
        {
            field.bricks[i] = field.bricks[i + 1];
        }
        size_t newCountBricks = field.countBricks;
        field.countBricks = --newCountBricks;
    }
}

void destroyField(Field& field)
{
    delete[] field.bricks;
}