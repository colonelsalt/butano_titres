#pragma once

#include "Tetramino.h"


static constexpr int num_tetraminos = 7;

static constexpr int i_index = 1;
static constexpr int j_index = 2;
static constexpr int l_index = 3;
static constexpr int o_index = 4;
static constexpr int s_index = 5;
static constexpr int t_index = 6;
static constexpr int z_index = 7;

Tetramino spawn_next();

extern const bn::sprite_item tetramino_sprite_items[num_tetraminos];