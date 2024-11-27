#include "game.h"

Game::Game()
{
    InitAudioDevice();
    SetTargetFPS(60);
    eat = LoadSound("sfx/eat.mp3");
    wall = LoadSound("sfx/wall.mp3");
}

Game::~Game()
{
    UnloadSound(eat);
    UnloadSound(wall);
    CloseAudioDevice();
}

void Game::Draw()
{
    DrawRectangleLinesEx(Rectangle{static_cast<float>(grid.offset - 5),
                                   static_cast<float>(grid.offset - 5),
                                   static_cast<float>(grid.cell_size * grid.cell_count + 10),
                                   static_cast<float>(grid.cell_size * grid.cell_count + 10)},
                                   5.0f,
                                   textColor);
    DrawText("Retro Snek", grid.offset-5, 20, 40, textColor);
    DrawText(TextFormat("%i", score), grid.offset-5, grid.offset+grid.cell_size*grid.cell_count+10, 40, textColor);
    player.Draw();
    food.Draw();
}

void Game::Update()
{
    if (IsKeyPressed(KEY_SPACE))
    {
        isRunning = true;
    }

    if (!isRunning)
    {
        return;
    }

    if (player.headPos() == food.getPos())
    {
        while (ElementInDeque(food.getPos(), player.getParts()))
        {
            PlaySound(eat);
            food.GenerateRandomPos();
            ++score;
        }

        player.setExtendSnake(true);
    }
    player.Update();
    food.Update();
    CheckCollision();
}

bool Game::ElementInDeque(Vector2 pos, std::deque<Vector2> parts)
{
    for (auto part : parts)
    {
        if (pos == part)
        {
            return true;
        }
    }

    return false;
}

void Game::GameOver()
{
    PlaySound(wall);
    player.reset();
    food.GenerateRandomPos();
    isRunning = false;
    score = 0;
}

void Game::CheckCollision()
{
    if (player.headPos().x == grid.cell_count || player.headPos().x == -1)
    {
        GameOver();
    }
    if (player.headPos().y == grid.cell_count || player.headPos().y == -1)
    {
        GameOver();
    }
    auto noHead = player.getParts();
    noHead.pop_front();
    if (ElementInDeque(player.getParts()[0], noHead))
    {
        GameOver();
    }
}
