#include <iostream>
#include <raylib.h>
#include "window.h"
#include "score_manager.h"
#include "ball.h"
#include "player.h"
#include "line.h"

Color green = Color{38, 185, 154, 255};
Color dark_green = Color{20, 160, 133, 255};
Color light_green = Color{129, 204, 184, 255};

Window window(1280, 720, "Pong");

int main()
{
    InitAudioDevice();
    Ball ball = {GetScreenWidth() / 2,GetScreenHeight() / 2, 5, 5, 20, WHITE};
    Player player(25, GetScreenHeight() / 2, 25, 120, WHITE);
    Computer computer(GetScreenWidth() - 25, GetScreenHeight() / 2, 25, 120, WHITE);
    Line line(GetScreenWidth() / 2, 0, GetScreenWidth() / 2, GetScreenHeight(), WHITE);
    ScoreManager scoreManager;

    SetTargetFPS(60);

    Sound sfxPong = LoadSound("sfx/pong.wav");

    while (!WindowShouldClose())
    {
        ball.Update();
        player.Update();
        computer.Update(ball.pos);
        if (CheckCollisionCircleRec(ball.pos, ball.radius, Rectangle{player.pos.x, player.pos.y, player.width, player.height}))
        {
            ball.vel.x *= -1.2;
            PlaySound(sfxPong);
        }
        if (CheckCollisionCircleRec(ball.pos, ball.radius, Rectangle{computer.pos.x, computer.pos.y, computer.width, computer.height}))
        {
            ball.vel.x *= -1.2;
            PlaySound(sfxPong);
        }

        BeginDrawing();
        ClearBackground(dark_green);
        DrawRectangle(GetScreenWidth() / 2, 0, GetScreenWidth() / 2, GetScreenHeight(), green);
        DrawCircle(GetScreenWidth() / 2, GetScreenHeight() / 2, 150, light_green);
        line.Draw();

        ball.Draw();
        player.Draw();
        computer.Draw();
        scoreManager.Draw();

        EndDrawing();
    }

    UnloadSound(sfxPong);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}