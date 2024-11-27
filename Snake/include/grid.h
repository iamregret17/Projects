#pragma once

struct Grid {
    const int cell_size;
    const int cell_count;
    const int offset{75};

    Grid(const int cell_size, const int cell_count);
    int getGridSize() const;
};

