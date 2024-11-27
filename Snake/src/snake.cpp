#include "snake.h"

Snake::Snake(const Grid &grid, double updateInterval)
    : grid(grid), updateInterval(updateInterval)
{
}

void Snake::Update()
{
    if (IsKeyPressed(KEY_A) && dir.x != 1)
        dir = {-1, 0};
    else if (IsKeyPressed(KEY_D) && dir.x != -1)
        dir = {1, 0};
    else if (IsKeyPressed(KEY_W) && dir.y != 1)
        dir = {0, -1};
    else if (IsKeyPressed(KEY_S) && dir.y != -1)
        dir = {0, 1};

    if (eventTriggered())
    {
        if (m_extendSnake == true)
        {
            extendSnake();
            m_extendSnake = false;
        }
        else
        {
            extendSnake();
            parts.pop_back();
        }
    }
}

void Snake::Draw()
{
    float cellSize = static_cast<float>(grid.cell_size);

    /* Draw evey part of the Snek */
    for (auto part : parts)
    {
        Rectangle rec{grid.offset + part.x * cellSize, grid.offset + part.y * cellSize, cellSize, cellSize};
        DrawRectangleRounded(rec, 0.5, 12, RAYWHITE);
    }
}

bool Snake::eventTriggered()
{
    double currentTime = GetTime();

    if (currentTime - lastUpdateTime >= updateInterval)
    {
        lastUpdateTime = currentTime;
        return true;
    }

    return false;
}

Vector2 Snake::headPos()
{
    return parts[0];
}

void Snake::extendSnake()
{
    parts.push_front(parts[0] + dir);
}

std::deque<Vector2> Snake::getParts() const
{
    return parts;
}

void Snake::setExtendSnake(bool set)
{
    m_extendSnake = set;
}

void Snake::reset()
{
    parts = {Vector2{6.0f, 9.0f},
             Vector2{5.0f, 9.0f},
             Vector2{4.0f, 9.0f}};
    dir = {1,0};
}