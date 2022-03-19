#include "Tetramino.h"
#include <bn_regular_bg_map_cell_info.h>
#include <bn_memory.h>
#include <bn_log.h>
#include <bn_assert.h>
#include <bn_fixed_point.h>

Tetramino::Tetramino(bn::sprite_ptr sprite, const bn::array<bool, num_tetramino_cells> collision_grid) : 
    _sprite(sprite), _collision_grid(collision_grid) 
{
    _grid_pos = bn::point(3, 0);
    _num_ticks_between_moves = 60;
    _tick_count = 0;
}

void Tetramino::update()
{
    _tick_count++;
    if (_tick_count >= _num_ticks_between_moves)
    {
        _tick_count = 0;
        move_down();
    }
}

bn::fixed_point Tetramino::grid_to_sprite_pos(bn::point grid_pos)
{
    return bn::fixed_point(8 * grid_pos.x() - 24, 8 * grid_pos.y() - 64);
}

void Tetramino::move_down()
{
    _grid_pos.set_y(_grid_pos.y() + 1);

    _sprite.value().set_position(grid_to_sprite_pos(_grid_pos));
}