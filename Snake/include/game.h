#pragma once
#include "window.h"
#include "grid.h"
#include "snake.h"
#include "food.h"

class Game {
private:
    Grid grid{30, 25}; 
    Window window{grid, "Snek"};
    Snake player{grid, 0.15};
    Food food{grid};
    bool gameOver{false};
    bool isRunning{false};
    unsigned int score{0};
    const Color textColor{20, 70, 20, 255};
    Sound eat;
    Sound wall;

public:
    Game();
    ~Game();
    void Draw();
    void Update();
    bool ElementInDeque(Vector2 pos, std::deque<Vector2> parts);
    void CheckCollision();
    void GameOver();
};
