#include "line.h"

void Line::Draw() const
{
    DrawLine(s_pos.x, s_pos.y, e_pos.x, e_pos.y, color);
}
