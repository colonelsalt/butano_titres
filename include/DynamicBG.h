#pragma once
#include <bn_point.h>
#include <bn_regular_bg_map_item.h>
#include <bn_regular_bg_map_ptr.h>
#include <bn_optional.h>
#include <bn_regular_bg_ptr.h>
#include "Common.h"

class DynamicBG
{
    protected: 
        bn::regular_bg_map_cell _bg_cells[BG_LENGTH * BG_LENGTH];
        bn::regular_bg_map_item _map_item;
        bn::optional<bn::regular_bg_ptr> _bg_ptr;
        bn::optional<bn::regular_bg_map_ptr> _bg_map;
    public:
        DynamicBG();
        void update();
        void add_cell(bn::point pos, int tile_index);
        void copy_cell_from_above(bn::point pos, int offset);
        void clear();
        void set_visible(bool visible);
        void set_alpha(bn::fixed alpha);
        void set_priority(int priority);
};