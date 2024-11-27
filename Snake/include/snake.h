#pragma once
#include <deque>
#include "raylib.h"
#include "grid.h"

class Snake
{
private:
    std::deque<Vector2> parts{Vector2{6.0f, 9.0f},
                              Vector2{5.0f, 9.0f},
                              Vector2{4.0f, 9.0f}};
    const Grid &grid;
    Vector2 dir{1,0};
    double lastUpdateTime{0};
    double updateInterval;
    bool m_extendSnake{false};

public:
    Snake(const Grid &grid, double updateInterval);
    bool eventTriggered();
    void Update();
    void Draw();
    Vector2 headPos();
    void extendSnake();
    std::deque<Vector2> getParts() const;
    void setExtendSnake(bool set);
    void reset();
};