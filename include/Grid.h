#pragma once
#include "Tetramino.h"
#include <bn_point.h>
#include <bn_regular_bg_map_item.h>
#include <bn_regular_bg_map_ptr.h>
#include <bn_optional.h>
#include <bn_regular_bg_ptr.h>

constexpr int GRID_WIDTH = 10;
constexpr int GRID_HEIGHT = 20;
constexpr int BG_LENGTH = 32;

class Grid 
{
    private: 
        bn::regular_bg_map_cell _bg_cells[BG_LENGTH * BG_LENGTH];
        bn::regular_bg_map_item _map_item;
        bn::optional<bn::regular_bg_ptr> _bg_ptr;
        bn::optional<bn::regular_bg_map_ptr> _bg_map;
    public:
        Grid();
        void update();
        void add_cell(bn::point pos, int tile_index);
};

void reset_grid();

bool did_collide(bn::point pos, t_col_grid& col_grid);

void add_to_grid(Tetramino& tetramino);