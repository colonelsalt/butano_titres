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

bool did_collide_with_left_wall(bn::point pos, t_col_grid col_grid)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (col_grid[j][i])
            {
                int adjacent_cell_x = pos.x() + i - 1;
                int cell_y = pos.y() + j;
                if (cell_y > GRID_HEIGHT - 1)
                {
                    continue;
                }
                if (adjacent_cell_x < 0 || bg_grid[cell_y][adjacent_cell_x])
                {
                    return true;
                }
            }
        }
        
    }
    return false;
}

bool did_collide_with_right_wall(bn::point pos, t_col_grid col_grid)
{
    for (int i = 3; i >= 0; i--)
    {
        for (int j = 0; j < 4; j++)
        {
            if (col_grid[j][i])
            {
                int adjacent_cell_x = pos.x() + i + 1;
                int cell_y = pos.y() + j;
                if (adjacent_cell_x > GRID_WIDTH - 1 || bg_grid[cell_y][adjacent_cell_x])
                {
                    return true;
                }

            }
        }
    }
    return false;
}