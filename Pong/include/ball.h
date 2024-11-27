#pragma once
#include "raylib.h"

class Ball
{
private:
    Sound sfxGoal = LoadSound("sfx/goal.wav");
    Color yellow = Color{243, 213, 91, 255};
    float speed = 5.0f;
    
public:
    Vector2 pos;
    Vector2 vel;
    float radius;
    Color color;

    Ball(Vector2 pos, Vector2 vel, float radius, Color color)
        : Ball(pos.x, pos.y, vel.x, vel.y, radius, color) {}

    template <typename T>
    Ball(T x, T y, T vel_x, T vel_y, T radius, Color color)
        : pos{static_cast<float>(x), static_cast<float>(y)},
          vel{static_cast<float>(vel_x), static_cast<float>(vel_y)},
          radius(static_cast<float>(radius)),
          color(color)
    {
    }

    ~Ball()
    {
        UnloadSound(sfxGoal);
    }

    void Draw() const;
    void Update();
    void Reset();
};