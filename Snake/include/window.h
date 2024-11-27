#pragma once

#include "grid.h"

class Window {
public:
    Window(const Grid &grid, const char *title);
    ~Window();
};
