#include "Util.h"

void copy_col_grid(t_col_grid& from, t_col_grid& to)
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            to[i][j] = from[i][j];
}

void rotate_col_grid_90(t_col_grid& grid)
{
    for (int i = 0; i < 2; i++)
    {
        for (int j = i; j < 4 - i - 1; j++)
        {
            bool temp = grid[i][j];
            grid[i][j] = grid[4 - 1 - j][i];
            grid[4 - 1 - j][i] = grid[4 - 1 - i][4 - 1 - j]; 
            grid[4 - 1 - i][4 - 1 - j] = grid[j][4 - 1 - i]; 
            grid[j][4 - 1 - i] = temp; 
        }
    }
}