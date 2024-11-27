#include "grid.h"

Grid::Grid(const int cell_size, const int cell_count)
    : cell_size(cell_size), cell_count(cell_count) {}

int Grid::getGridSize() const
{
    return cell_size * cell_count;
}