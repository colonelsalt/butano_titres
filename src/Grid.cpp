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
    //BN_LOG("Adding to cell at position: ", pos.x(), ", ", pos.y());
    bn::regular_bg_map_cell& cell = _bg_cells[_map_item.cell_index(pos.x(), pos.y())];
    bn::regular_bg_map_cell_info cell_info(cell);

    cell_info.set_tile_index(tile_index);
    cell = cell_info.cell();
    update();
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
                BN_LOG("Adding cell to grid at x = ", x, ", y = ", y);
                bg_grid[y][x] = true;
                grid_ptr->add_cell(bn::point(x, y), tetramino.index() + 1);
            }
        }
    }

}