#pragma once
#include "raylib.h"
#include "grid.h"

class Food {
private:
    Texture2D texture;
    Vector2 pos;
    const Grid &grid;


public:
    Food(const Grid &grid);
    ~Food();
    void Update();
    void Draw();
    void GenerateRandomPos();
    Vector2 getPos() const;
};