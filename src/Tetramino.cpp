#include "Tetramino.h"
#include <bn_regular_bg_map_cell_info.h>
#include <bn_memory.h>
#include <bn_log.h>
#include <bn_assert.h>
#include <bn_fixed_point.h>
#include <bn_keypad.h>
#include "Grid.h"
#include "Util.h"

Tetramino::Tetramino(bn::array<t_col_grid, 4> collision_grids, DynamicBG* tetramino_bg,
                    DynamicBG* ghost_piece_bg, t_wall_kick_list wall_kicks_list, int tile_index) : 
    _col_grids(collision_grids), _active_col_grid(collision_grids[0]), _tile_index(tile_index),
    _rotation_index(0), _grid_pos(3, 0), _ghost_piece(ghost_piece_bg, tile_index), _wall_kicks_list(wall_kicks_list),
    _bg(tetramino_bg)
{
    _num_ticks_between_moves = 100;
    _tick_count = 0;
    _has_collided = false;
    _input_repeat_rate = 6;
    _input_repeat_count = 0;

    _bg->clear();
    _bg->set_priority(2);
    _bg->set_visible(true);

    _ghost_piece.set_colour(tile_index + 1);
    _ghost_piece.update_pos(_grid_pos, _active_col_grid);
    _ghost_piece.set_visible(true);
}

void Tetramino::update()
{
    handle_input();
    _tick_count++;
    if (_tick_count >= _num_ticks_between_moves)
    {
        _tick_count = 0;
        move_down();
    }
    if (_has_collided)
        _ghost_piece.set_visible(false);

    _bg->clear();
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (_active_col_grid[i][j])
                _bg->add_cell(bn::point(_grid_pos.x() + j, _grid_pos.y() + i), _tile_index + 1);
    _bg->update();
}

void Tetramino::handle_input()
{
    if (_has_collided)
        return;
    
    if (bn::keypad::a_pressed())
        rotate_clockwise();
    
    if (bn::keypad::left_pressed() || bn::keypad::right_pressed() || bn::keypad::down_pressed())
        _input_repeat_count = 0;
    
    if (bn::keypad::left_held() || bn::keypad::right_held() || bn::keypad::down_held())
    {
        if (_input_repeat_count == 0)
        {
            if (bn::keypad::left_held())
                move_left();
            if (bn::keypad::right_held())
                move_right();
            if (bn::keypad::down_held())
                move_down();
        }
        _input_repeat_count = (_input_repeat_count + 1) % _input_repeat_rate;
    }
    else if (bn::keypad::up_pressed())
        hard_drop();
}

void Tetramino::move_down()
{
    if (did_collide(bn::point(_grid_pos.x(), _grid_pos.y() + 1), _active_col_grid))
    {
        _has_collided = true;
        //BN_LOG("Tetramino collided; index: ", _index);
    }
    else
    {
        _grid_pos.set_y(_grid_pos.y() + 1);
        _ghost_piece.update_pos(_grid_pos, _active_col_grid);
    }
}

void Tetramino::move_right()
{
    if (!did_collide(bn::point(_grid_pos.x() + 1, _grid_pos.y()), _active_col_grid))
    {
        _grid_pos.set_x(_grid_pos.x() + 1);
        _ghost_piece.update_pos(_grid_pos, _active_col_grid);
    }
}

void Tetramino::move_left()
{
    if (!did_collide(bn::point(_grid_pos.x() - 1, _grid_pos.y()), _active_col_grid))
    {
        _grid_pos.set_x(_grid_pos.x() - 1);
        _ghost_piece.update_pos(_grid_pos, _active_col_grid);
    }
}

void Tetramino::hard_drop()
{
    _grid_pos = _ghost_piece.get_pos();
    _has_collided = true;
}

void Tetramino::rotate_clockwise()
{
    int new_rot_index = (_rotation_index + 1) % 4;
    
    bool valid_rotation = true;
    if (did_collide(_grid_pos, _col_grids[new_rot_index]))
    {
        valid_rotation = false;
        bn::array<bn::point, 4> wall_kicks = _wall_kicks_list[new_rot_index];
        for (int i = 0; i < 4; i++)
        {
            if (wall_kicks[i].x() == -69)
                break;
            bn::point new_pos = _grid_pos + wall_kicks[i];
            if (!did_collide(new_pos, _col_grids[new_rot_index]))
            {
                valid_rotation = true;
                _grid_pos = new_pos;
                break;
            }
        }
    }
    if (!valid_rotation)
        return;
        
    _active_col_grid = _col_grids[new_rot_index];
    _rotation_index = new_rot_index;
    _ghost_piece.update_pos(_grid_pos, _active_col_grid);
}

void Tetramino::hide()
{
    _bg->set_visible(false);
}

bool Tetramino::has_collided()
{
    return _has_collided;
}

t_col_grid Tetramino::collision_grid()
{
    return _active_col_grid;
}

int Tetramino::index()
{
    return _tile_index;
}

bn::point Tetramino::grid_pos()
{
    return _grid_pos;
}