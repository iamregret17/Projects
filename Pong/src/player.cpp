#include "player.h"

void Player::Draw() const
{
    DrawRectangleRounded(Rectangle{pos.x, pos.y, width, height}, 0.8, 0, WHITE);
}

void Player::Update()
{
    if (IsKeyDown(KEY_W))
    {
        pos.y -= vel.y;
        if (pos.y + height <= 0)
        {
            pos.y = GetScreenHeight() + height / 2;
        }
    }
    else if (IsKeyDown(KEY_S))
    {
        pos.y += vel.y;
        if (pos.y - height / 2 >= GetScreenHeight())
        {
            pos.y = 0 - height;
        }
    }
}

void Computer::Update(Vector2 track)
{
    if (pos.y >= track.y && track.x)
    {
        pos.y = pos.y - vel.y;
    }
    if (pos.y <= track.y && track.x)
    {
        pos.y = pos.y + vel.y;
    }
}