#include "GhostPiece.h"
#include <bn_log.h>
#include "bn_regular_bg_items_tetraminos.h"
#include "bn_regular_bg_map_cell_info.h"
#include "Grid.h"

GhostPiece::GhostPiece(DynamicBG* bg, int tile_index) : _bg(bg), _tile_index(tile_index), _pos(0, 0)
{
    _bg->clear();
    _bg->set_alpha(0.8);
}

void GhostPiece::grid_to_bg(bn::point start_pos, t_col_grid& col_grid)
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (col_grid[i][j])
                _bg->add_cell(bn::point(start_pos.x() + j, start_pos.y() + i), _tile_index);
    _bg->update();
}

void GhostPiece::set_colour(int tile_index)
{
    _tile_index = tile_index;
}

void GhostPiece::update_pos(bn::point tetramino_pos, t_col_grid& col_grid)
{
    _bg->clear();
    bn::point pos = tetramino_pos;
    while(!did_collide(pos, col_grid))
        pos.set_y(pos.y() + 1);
    pos.set_y(pos.y() - 1);
    grid_to_bg(pos, col_grid);
    _pos = pos;
}

bn::point GhostPiece::get_pos()
{
    return _pos;
}

void GhostPiece::set_visible(bool visible)
{
    _bg->set_visible(visible);
}