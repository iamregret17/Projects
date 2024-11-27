#pragma once
#include "raylib.h"

class Line
{
public:
    Vector2 s_pos;
    Vector2 e_pos;
    Color color;

    Line(Vector2 s_pos, Vector2 e_pos, Color color)
        : s_pos(s_pos), e_pos(e_pos), color(color) {}

    template <typename T>
    Line(T s_posx, T s_posy, T e_posx, T e_posy, Color color)
        : s_pos{static_cast<float>(s_posx), static_cast<float>(s_posy)},
          e_pos{static_cast<float>(e_posx), static_cast<float>(e_posy)},
          color(color) {}

    void Draw() const;
};