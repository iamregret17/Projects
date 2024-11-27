#include "food.h"

Food::Food(const Grid &grid)
    : grid(grid)
{
    Image image = LoadImage("img/food.png");
    texture = LoadTextureFromImage(image);
    UnloadImage(image);

    GenerateRandomPos();
}

Food::~Food()
{
    UnloadTexture(texture);
}

void Food::Update()
{
    GetRandomValue(0, GetScreenWidth());
}

void Food::Draw()
{
    DrawTexture(texture, grid.offset + pos.x * grid.cell_size, grid.offset + pos.y * grid.cell_size, WHITE);
}

void Food::GenerateRandomPos()
{
    float x = GetRandomValue(0, grid.cell_count - 1); 
    float y = GetRandomValue(0, grid.cell_count - 1); 
    pos = {x,y};
}

Vector2 Food::getPos() const
{
    return pos;
}