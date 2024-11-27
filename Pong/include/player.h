#pragma once
#include "raylib.h"

class Player
{
protected:
    Vector2 vel{5, 5};

public:
    Vector2 pos;
    float width;
    float height;
    Color color;

    Player(Vector2 pos, float width, float height, Color color)
        : Player(pos.x, pos.y, width, height, color) {}

    template <typename T>
    Player(T x, T y, T width, T height, Color color)
        : pos{static_cast<float>(x - width / 2), static_cast<float>(y - height / 2)},
          width(static_cast<float>(width)),
          height(static_cast<float>(height)),
          color(color) {}

    void Update();
    void Draw() const;
};

class Computer : public Player {
public:
    template <typename T>
    Computer(T x, T y, T width, T height, Color color)
        : Player(x, y, width, height, color) {}

    void Update(Vector2 track);
};

