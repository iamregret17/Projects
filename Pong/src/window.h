#pragma once

class Window {
public:
    int width;
    int height;
    const char* title;

    Window(int width, int height, const char* title)
        : width(width), height(height), title(title) 
    {
        InitWindow(width, height, title);
    }
};