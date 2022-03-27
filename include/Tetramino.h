#pragma once

#include <bn_array.h>
#include <bn_fixed.h>
#include <bn_sprite_ptr.h>
#include <bn_optional.h>
#include <bn_point.h>
#include <bn_size.h>
#include "GhostPiece.h"
#include "Common.h"

class Tetramino
{
    private:
        t_col_grid _active_col_grid;
        bn::array<t_col_grid, 4> _col_grids;
        DynamicBG* _bg;

        GhostPiece _ghost_piece;
        int _tile_index;
        int _rotation_index;
        
        // Position of the top left corner of this tetramino's grid in the BG grid
        bn::point _grid_pos;
        int _num_ticks_between_moves;
        int _tick_count;
        bn::size _size;
        bool _has_collided;
        int _input_repeat_rate;
        int _input_repeat_count;

        void handle_input();
        void rotate_clockwise();
        void move_down();
        void move_right();
        void move_left();
        void hard_drop();
        bn::fixed_point grid_to_sprite_pos(bn::point grid_pos);

    public:
        Tetramino(bn::array<t_col_grid, 4> collision_grids, DynamicBG* tetramino_bg, DynamicBG* ghost_piece_bg, int tile_index);
        void update();
        void hide();
        bool has_collided();
        t_col_grid collision_grid();
        int index();
        bn::point grid_pos();

};
