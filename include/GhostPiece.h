#pragma once
#include "Common.h"
#include <bn_regular_bg_map_item.h>
#include <bn_regular_bg_map_ptr.h>
#include <bn_optional.h>
#include <bn_regular_bg_ptr.h>
#include "DynamicBG.h"

class GhostPiece
{
    private:
        DynamicBG* _bg;
        int _tile_index;
        bn::point _pos;

        void grid_to_bg(bn::point start_pos, t_col_grid& col_grid);

    public:
        GhostPiece(DynamicBG* bg, int tile_index);
        void set_colour(int tile_index);
        void update_pos(bn::point tetramino_pos, t_col_grid& col_grid);
        void set_visible(bool visible);
        bn::point get_pos();
};