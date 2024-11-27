#include "ball.h"
#include "score_manager.h"

void Ball::Draw() const
{
    DrawCircle(pos.x, pos.y, radius, yellow);
}

void Ball::Update()
{
    pos.x += vel.x;
    pos.y += vel.y;

    if (pos.y + radius >= GetScreenHeight() || pos.y - radius <= 0)
    {
        vel.y *= -1;
    }
    if (pos.x >= GetScreenWidth() + radius)
    {
        ScoreManager::player_score++;
        PlaySound(sfxGoal);
        WaitTime(1.0f);
        Reset();
    }

    if (pos.x <= -radius)
    {
        ScoreManager::computer_score++;
        PlaySound(sfxGoal);
        WaitTime(1.0f);
        Reset();
    }
}

void Ball::Reset()
{
    // Reset the ball to center
    pos = {static_cast<float>(GetScreenWidth() / 2),
           static_cast<float>(GetScreenHeight() / 2)};

    // Randomly throw the ball
    int xDirection = GetRandomValue(0, 1) == 0 ? -1 : 1;
    int yDirection = GetRandomValue(0, 1) == 0 ? -1 : 1;

    vel = {speed * xDirection, speed * yDirection};
}

