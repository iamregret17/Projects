#pragma once
#include "ball.h"

class ScoreManager {
public:
    static unsigned int player_score;
    static unsigned int computer_score;

    friend class Ball;

    void Draw();
};