#include "window.h"
#include "raylib.h"

Window::Window(const Grid &grid, const char *title)
{
    InitWindow(2 * grid.offset + grid.getGridSize(), 2 * grid.offset + grid.getGridSize(), title);
}

Window::~Window()
{
    CloseWindow();
}