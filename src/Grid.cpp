#include "Grid.h"
#include <bn_array.h>
#include <bn_log.h>
#include "bn_regular_bg_items_tetraminos.h"
#include "bn_regular_bg_map_cell_info.h"
#include <bn_display.h>

bn::array<bn::array<bool, GRID_WIDTH>, GRID_HEIGHT> bg_grid; 
bn::unique_ptr<Grid> grid_ptr;

Grid::Grid() : _map_item(_bg_cells[0], bn::size(BG_LENGTH, BG_LENGTH))
{
    bn::regular_bg_item bg_item(bn::regular_bg_items::tetraminos.tiles_item(),
        bn::regular_bg_items::tetraminos.palette_item(), _map_item);
    _bg_ptr = bg_item.create_bg(88, 48);
    _bg_map = _bg_ptr.value().map();

    bn::memory::clear(BG_LENGTH * BG_LENGTH, _bg_cells[0]);
}

void Grid::update()
{
    _bg_map.value().reload_cells_ref();
}

void Grid::add_cell(bn::point pos, int tile_index)
{
    bn::regular_bg_map_cell& cell = _bg_cells[_map_item.cell_index(pos.x(), pos.y())];
    bn::regular_bg_map_cell_info cell_info(cell);

    cell_info.set_tile_index(tile_index);
    cell = cell_info.cell();
    update();
}

void Grid::copy_cell_from_above(bn::point pos, int offset)
{
    bn::regular_bg_map_cell& cell_above = _bg_cells[_map_item.cell_index(pos.x(), pos.y() - offset)];
    bn::regular_bg_map_cell_info cell_above_info(cell_above);
    add_cell(pos, cell_above_info.tile_index());
}


void reset_grid()
{
    grid_ptr = bn::unique_ptr<Grid>(new Grid());
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
                //BN_LOG("Adding cell to grid at x = ", x, ", y = ", y);
                bg_grid[y][x] = true;
                grid_ptr->add_cell(bn::point(x, y), tetramino.index() + 1);
            }
        }
    }
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

