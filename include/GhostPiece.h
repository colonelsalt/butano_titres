#pragma once
#include "Common.h"
#include <bn_regular_bg_map_item.h>
#include <bn_regular_bg_map_ptr.h>
#include <bn_optional.h>
#include <bn_regular_bg_ptr.h>

class GhostPiece
{
    private:
        bn::regular_bg_map_cell _bg_cells[BG_LENGTH * BG_LENGTH];
        bn::regular_bg_map_item _map_item;
        bn::optional<bn::regular_bg_ptr> _bg_ptr;
        bn::optional<bn::regular_bg_map_ptr> _bg_map;
        int _tile_index;
        
        void clear_tiles();
        void add_tile(bn::point pos);
        void grid_to_bg(bn::point start_pos, t_col_grid& col_grid);

    public:
        GhostPiece();
        void set_colour(int tile_index);
        void update_pos(bn::point tetramino_pos, t_col_grid& col_grid);
        void set_visible(bool visible);
};