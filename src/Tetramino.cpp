#include "Tetramino.h"
#include <bn_regular_bg_map_cell_info.h>
#include <bn_memory.h>
#include <bn_log.h>
#include <bn_assert.h>
#include <bn_fixed_point.h>
#include <bn_keypad.h>

Tetramino::Tetramino(bn::sprite_ptr sprite, const bn::array<bn::array<bool, 4>, 4> collision_grid) : 
    _sprite(sprite), _collision_grid(collision_grid), _size(sprite.dimensions().width() / 8, sprite.dimensions().height() / 8)
{
    _grid_pos = bn::point(3, 0);
    _num_ticks_between_moves = 60;
    _tick_count = 0;
}

void Tetramino::update()
{
    if (bn::keypad::a_pressed())
    {
        rotate_clockwise();
    }

    _tick_count++;
    if (_tick_count >= _num_ticks_between_moves)
    {
        _tick_count = 0;
        move_down();
    }
}

bn::fixed_point Tetramino::grid_to_sprite_pos(bn::point grid_pos)
{
    int sprite_x = 8 * grid_pos.x() + (_sprite.value().dimensions().width() / 2) - 40;
    int sprite_y = 8 * grid_pos.y() + (_sprite.value().dimensions().height() / 2) - 80;
    return bn::fixed_point(sprite_x, sprite_y);
}

void Tetramino::move_down()
{
    _grid_pos.set_y(_grid_pos.y() + 1);

    _sprite.value().set_position(grid_to_sprite_pos(_grid_pos));
}

void Tetramino::rotate_clockwise()
{
    // Rotate collision grid
    // for (int i = 0; i < 2; i++)
    // {
    //     for (int j = i; j < 4 - i - 1; j++)
    //     {
    //         bool temp = _collision_grid[i][j];
    //         _collision_grid[i][j] = _collision_grid[4 - i - j][i];
    //         _collision_grid[4 - 1 - j][i] = _collision_grid[4 - 1 - i][4 - 1 - j]; 
    //         _collision_grid[4 - 1 - i][4 - 1 - j] = _collision_grid[j][4 - 1 - i]; 
    //         _collision_grid[j][4 - 1 - i] = temp; 
    //     }
    // }
    
    int new_angle = (_sprite.value().rotation_angle() + 90).integer() % 360;

    _sprite.value().set_rotation_angle(new_angle);
}