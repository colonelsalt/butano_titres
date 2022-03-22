#pragma once
#include "Tetramino.h"
#include <bn_point.h>

constexpr int GRID_WIDTH = 10;
constexpr int GRID_HEIGHT = 20;

class Grid 
{

};

bool did_collide(bn::point pos, t_col_grid col_grid);

void add_to_grid(Tetramino& tetramino);