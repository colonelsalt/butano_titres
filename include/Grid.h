#pragma once
#include "Tetramino.h"
#include <bn_point.h>
#include "Common.h"

void reset_grid();
bool did_collide(bn::point pos, t_col_grid& col_grid);
void add_to_grid(Tetramino& tetramino);
bool check_for_line_clear();
void shift_down_cleared_lines();