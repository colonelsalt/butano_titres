#include "Grid.h"
#include <bn_array.h>
#include <bn_log.h>

bn::array<bn::array<bool, GRID_WIDTH>, GRID_HEIGHT> bg_grid; 

void reset_grid()
{
    for (int i = 0; i < GRID_HEIGHT; i++)
    {
        for (int j = 0; j < GRID_WIDTH; j++)
        {
            bg_grid[i][j] = false;
        }
    }
}

bool did_collide(bn::point pos, t_col_grid col_grid)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (col_grid[i][j])
            {
                int x = pos.x() + j;
                int y = pos.y() + i;
                if (x < 0 || x > GRID_WIDTH - 1 || y < 0 || y > GRID_HEIGHT - 1)
                    return true;
                else if (bg_grid[y][x])
                    return true;
            }
        }
    }
    return false;
}