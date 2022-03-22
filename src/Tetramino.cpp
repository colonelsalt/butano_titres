#include "Tetramino.h"
#include <bn_regular_bg_map_cell_info.h>
#include <bn_memory.h>
#include <bn_log.h>
#include <bn_assert.h>
#include <bn_fixed_point.h>
#include <bn_keypad.h>
#include "Grid.h"
#include "Util.h"

Tetramino::Tetramino(bn::sprite_ptr sprite, const bn::array<bn::array<bool, 4>, 4> collision_grid) : 
    _sprite(sprite), _collision_grid(collision_grid), _size(sprite.dimensions().width() / 8, sprite.dimensions().height() / 8)
{
    _grid_pos = bn::point(3, 0);
    _num_ticks_between_moves = 100;
    _tick_count = 0;
    _has_collided = false;
}

void Tetramino::update()
{
    if (bn::keypad::a_pressed())
    {
        rotate_clockwise();
    }
    if (bn::keypad::left_held())
    {
        move_left();
    }
    else if (bn::keypad::right_held())
    {
        move_right();
    }

    _tick_count++;
    if (_tick_count >= _num_ticks_between_moves)
    {
        _tick_count = 0;
        move_down();
    }
    _sprite.value().set_position(grid_to_sprite_pos(_grid_pos));
}

bn::fixed_point Tetramino::grid_to_sprite_pos(bn::point grid_pos)
{
    int sprite_x = 8 * grid_pos.x() + (_sprite.value().dimensions().width() / 2) - 40;
    int sprite_y = 8 * grid_pos.y() + (_sprite.value().dimensions().height() / 2) - 80;
    return bn::fixed_point(sprite_x, sprite_y);
}

void Tetramino::move_down()
{
    if (did_collide(bn::point(_grid_pos.x(), _grid_pos.y() + 1), _collision_grid))
    {
        _has_collided = true;
    }
    else
    {
        _grid_pos.set_y(_grid_pos.y() + 1);
    }
}

void Tetramino::move_right()
{
    if (!did_collide(bn::point(_grid_pos.x() + 1, _grid_pos.y()), _collision_grid))
    {
        _grid_pos.set_x(_grid_pos.x() + 1);
    }
}

void Tetramino::move_left()
{
    if (!did_collide(bn::point(_grid_pos.x() - 1, _grid_pos.y()), _collision_grid))
    {
        _grid_pos.set_x(_grid_pos.x() - 1);
    }
}

void Tetramino::rotate_clockwise()
{
    t_col_grid new_rot_grid;
    copy_col_grid(_collision_grid, new_rot_grid);
    rotate_col_grid_90(new_rot_grid);
    if (did_collide(_grid_pos, new_rot_grid))
        return;

    copy_col_grid(new_rot_grid, _collision_grid);
    int new_angle = (_sprite.value().rotation_angle() + 270).integer() % 360;

    _sprite.value().set_rotation_angle(new_angle);
}

bool Tetramino::has_collided()
{
    return _has_collided;
}