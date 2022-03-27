#include "GhostPiece.h"
#include <bn_log.h>
#include "bn_regular_bg_items_tetraminos.h"
#include "bn_regular_bg_map_cell_info.h"
#include <bn_blending.h>
#include "Grid.h"

GhostPiece::GhostPiece() : _map_item(_bg_cells[0], bn::size(BG_LENGTH, BG_LENGTH)), _tile_index(0)
{
    bn::regular_bg_item bg_item(bn::regular_bg_items::tetraminos.tiles_item(),
        bn::regular_bg_items::tetraminos.palette_item(), _map_item);
    _bg_ptr = bg_item.create_bg(88, 48);
    _bg_map = _bg_ptr.value().map();

    _bg_ptr.value().set_blending_enabled(true);
    bn::blending::set_fade_alpha(0.8);
}

void GhostPiece::clear_tiles()
{
    bn::memory::clear(BG_LENGTH * BG_LENGTH, _bg_cells[0]);
}

void GhostPiece::add_tile(bn::point pos)
{
    bn::regular_bg_map_cell& cell = _bg_cells[_map_item.cell_index(pos.x(), pos.y())];
    bn::regular_bg_map_cell_info cell_info(cell);

    cell_info.set_tile_index(_tile_index);
    cell = cell_info.cell();
}

void GhostPiece::grid_to_bg(bn::point start_pos, t_col_grid& col_grid)
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (col_grid[i][j])
                add_tile(bn::point(start_pos.x() + j, start_pos.y() + i));
    _bg_map.value().reload_cells_ref();
}

void GhostPiece::set_colour(int tile_index)
{
    _tile_index = tile_index;
}

void GhostPiece::update_pos(bn::point tetramino_pos, t_col_grid& col_grid)
{
    clear_tiles();
    bn::point pos = tetramino_pos;
    while(!did_collide(pos, col_grid))
        pos.set_y(pos.y() + 1);
    pos.set_y(pos.y() - 1);
    grid_to_bg(pos, col_grid);
}

void GhostPiece::set_visible(bool visible)
{
    _bg_ptr.value().set_visible(visible);
}