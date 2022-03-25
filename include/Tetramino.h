#pragma once

#include <bn_array.h>
#include <bn_fixed.h>
#include <bn_sprite_ptr.h>
#include <bn_optional.h>
#include <bn_point.h>
#include <bn_size.h>

constexpr int num_tetramino_cells = 4 * 4;
typedef bn::array<bn::array<bool, 4>, 4> t_col_grid;
class Tetramino
{
    private:
        bn::optional<bn::sprite_ptr> _sprite;
        t_col_grid _collision_grid;
        int _index;
        
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
        bn::fixed_point grid_to_sprite_pos(bn::point grid_pos);

    public:
        Tetramino(bn::sprite_ptr sprite, t_col_grid collision_grid, int index);
        void update();
        void hide();
        bool has_collided();
        t_col_grid collision_grid();
        int index();
        bn::point grid_pos();

};
