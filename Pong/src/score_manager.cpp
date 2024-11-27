#include "score_manager.h"
#include "raylib.h"

unsigned int ScoreManager::player_score = 0;
unsigned int ScoreManager::computer_score = 0;

void ScoreManager::Draw()
{
    DrawText(TextFormat("%i", player_score), GetScreenWidth()/4 - 20, 20, 80, WHITE);
    DrawText(TextFormat("%i", computer_score), 3 * GetScreenWidth()/4, 20, 80, WHITE);
}