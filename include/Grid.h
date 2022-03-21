#pragma once
#include "Tetramino.h"
#include <bn_point.h>

constexpr int GRID_WIDTH = 10;
constexpr int GRID_HEIGHT = 20;

class Grid 
{

};

bool did_collide_with_left_wall(bn::point pos, t_col_grid col_grid);
bool did_collide_with_right_wall(bn::point pos, t_col_grid col_grid);