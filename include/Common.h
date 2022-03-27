#pragma once

#include <bn_array.h>
#include <bn_fixed.h>
#include <bn_sprite_ptr.h>
#include <bn_optional.h>
#include <bn_point.h>
#include <bn_size.h>

constexpr int GRID_WIDTH = 10;
constexpr int GRID_HEIGHT = 20;
constexpr int BG_LENGTH = 32;

constexpr int num_tetramino_cells = 4 * 4;
typedef bn::array<bn::array<bool, 4>, 4> t_col_grid;