#include "Grid.h"
#include <bn_array.h>
#include <bn_log.h>
#include "bn_regular_bg_items_tetraminos.h"
#include "bn_regular_bg_map_cell_info.h"
#include <bn_display.h>
#include "DynamicBG.h"

bn::array<bn::array<bool, GRID_WIDTH>, GRID_HEIGHT> bg_grid; 
bn::unique_ptr<DynamicBG> grid_ptr;

void reset_grid()
{
    grid_ptr = bn::unique_ptr<DynamicBG>(new DynamicBG());
    grid_ptr->set_visible(true);
    grid_ptr->set_priority(3);
    for (int i = 0; i < GRID_HEIGHT; i++)
        for (int j = 0; j < GRID_WIDTH; j++)
            bg_grid[i][j] = false;
}

bool did_collide(bn::point pos, t_col_grid& col_grid)
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

void add_to_grid(Tetramino& tetramino)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (tetramino.collision_grid()[i][j])
            {
                int x = tetramino.grid_pos().x() + j;
                int y = tetramino.grid_pos().y() + i;
                if (x < 0 || x > GRID_WIDTH - 1 || y < 0 || y > GRID_HEIGHT - 1)
                    continue;
                BN_LOG("Adding cell to grid at x = ", x, ", y = ", y, " with tile index: ", tetramino.index() + 1);
                bg_grid[y][x] = true;
                grid_ptr->add_cell(bn::point(x, y), tetramino.index() + 1);
            }
        }
    }
    grid_ptr->update();
}

bn::array<int, 4> lines_cleared;
bool check_for_line_clear()
{
    lines_cleared.fill(-1);
    int cleared_rows_index = 0;
    for (int i = 0; i < GRID_HEIGHT; i++)
    {
        bool line_cleared = true;
        for (int j = 0; j < GRID_WIDTH; j++)
            line_cleared = line_cleared && bg_grid[i][j];
        
        if (line_cleared)
        {
            lines_cleared[cleared_rows_index++] = i;
            BN_LOG("Line clear on line ", i);
            for (int j = 0; j < GRID_WIDTH; j++)
            {
                bg_grid[i][j] = false;
                grid_ptr->add_cell(bn::point(j, i), 8);
            }
        }
    }
    grid_ptr->update();
    return cleared_rows_index > 0;
}

void shift_down(int start_line, int num_lines)
{
    BN_LOG("Shifting lines from ", start_line, " and up by ", num_lines);

    for (int i = start_line; i >= 0; i--)
    {
        for (int j = 0; j < GRID_WIDTH; j++)
        {
            if (i - num_lines < 0)
            {
                bg_grid[i][j] = false;
                grid_ptr->add_cell(bn::point(j, i), 0);
            }
            else
            {
                bg_grid[i][j] = bg_grid[i - num_lines][j];
                grid_ptr->copy_cell_from_above(bn::point(j, i), num_lines);
            }
        }
    }
    grid_ptr->update();
}

void shift_down_cleared_lines()
{
    int last_line = -1;
    int num_consecutive_lines = 0;
    int lines_already_shifted = 0;

    for (int i = 0; i < 4; i++)
    {
        if (lines_cleared[i] == -1)
        {
            if (num_consecutive_lines > 0)
            {
                shift_down(last_line + lines_already_shifted, num_consecutive_lines);
                lines_already_shifted += num_consecutive_lines;
                num_consecutive_lines = 0;
            }
        }
        else
        {
            if (last_line == -1 || lines_cleared[i] == last_line + 1)
                num_consecutive_lines++;

        }
        last_line = lines_cleared[i];
    }
    if (last_line != -1)
    {
        shift_down(last_line + lines_already_shifted, num_consecutive_lines);
    }
}

