#include <raylib.h>
#include "game.h"


int main()
{
    Color darkGreen = Color{60, 179, 113, 255};
    Game game;

    while (!WindowShouldClose())
    {
        game.Update();

        BeginDrawing();
        ClearBackground(darkGreen);

        game.Draw();

        EndDrawing();
    }

    return 0;
}