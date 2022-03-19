#pragma once

#include <bn_array.h>
#include <bn_fixed.h>
#include <bn_sprite_ptr.h>
#include <bn_optional.h>
#include <bn_point.h>

constexpr int num_tetramino_cells = 4 * 4;
class Tetramino
{
    private:
        bn::optional<bn::sprite_ptr> _sprite;
        const bn::array<bool, num_tetramino_cells> _collision_grid;
        
        // Position of the top left corner of this tetramino's grid in the BG grid
        bn::point _grid_pos;
        int _num_ticks_between_moves;
        int _tick_count;

        void move_down();
        bn::fixed_point grid_to_sprite_pos(bn::point grid_pos);

    public:
        Tetramino(bn::sprite_ptr sprite, const bn::array<bool, num_tetramino_cells>);
        void update();

};
