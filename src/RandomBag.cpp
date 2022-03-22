#include "RandomBag.h"
#include <bn_display.h>
#include <bn_fixed.h>
#include <bn_array.h>
#include <bn_random.h>
#include <bn_fixed.h>
#include "bn_sprite_items_i_tetramino.h"
#include "bn_sprite_items_j_tetramino.h"
#include "bn_sprite_items_l_tetramino.h"
#include "bn_sprite_items_o_tetramino.h"
#include "bn_sprite_items_s_tetramino.h"
#include "bn_sprite_items_t_tetramino.h"
#include "bn_sprite_items_z_tetramino.h"

static constexpr t_col_grid i_tetramino_grid =
{{
    { 0, 0, 0, 0 },
    { 1, 1, 1, 1 },
    { 0, 0, 0, 0 },
    { 0, 0, 0, 0 }
}};

static constexpr t_col_grid o_tetramino_grid =
{{
    { 0, 0, 0, 0 },
    { 0, 1, 1, 0 },
    { 0, 1, 1, 0 },
    { 0, 0, 0, 0 }
}};

static constexpr t_col_grid j_tetramino_grid =
{{
    { 0, 1, 0, 0 },
    { 0, 1, 1, 1 },
    { 0, 0, 0, 0 },
    { 0, 0, 0, 0 }
}};

static constexpr t_col_grid l_tetramino_grid =
{{
    { 0, 0, 0, 1 },
    { 0, 1, 1, 1 },
    { 0, 0, 0, 0 },
    { 0, 0, 0, 0 }
}};

static constexpr t_col_grid s_tetramino_grid =
{{
    { 0, 0, 1, 1 },
    { 0, 1, 1, 0 },
    { 0, 0, 0, 0 },
    { 0, 0, 0, 0 }
}};

static constexpr t_col_grid t_tetramino_grid =
{{
    { 0, 1, 0, 0 },
    { 1, 1, 1, 0 },
    { 0, 0, 0, 0 },
    { 0, 0, 0, 0 }
}};

static constexpr t_col_grid z_tetramino_grid =
{{
    { 0, 1, 1, 0 },
    { 0, 0, 1, 1 },
    { 0, 0, 0, 0 },
    { 0, 0, 0, 0 }
}};

static constexpr bn::array<t_col_grid, num_tetraminos> collision_grids =
{
    i_tetramino_grid,
    j_tetramino_grid,
    l_tetramino_grid,
    o_tetramino_grid,
    s_tetramino_grid,
    t_tetramino_grid,
    z_tetramino_grid
};

static bn::array<int, num_tetraminos> tetramino_index_bag = { 0, 1, 2, 3, 4, 5, 6 };

const bn::sprite_item tetramino_sprite_items[num_tetraminos] =
{ 
    bn::sprite_items::i_tetramino,
    bn::sprite_items::j_tetramino,
    bn::sprite_items::l_tetramino,
    bn::sprite_items::o_tetramino,
    bn::sprite_items::s_tetramino,
    bn::sprite_items::t_tetramino,
    bn::sprite_items::z_tetramino
};

constexpr int turns_between_shuffles = 7;
constexpr bn::fixed spawn_y = (-bn::display::height() / 2) + 16;

bn::random random = bn::random();
int curr_turn = 0;

void shuffle_bag(bn::array<int, num_tetraminos>& bag)
{
    int curr_index = num_tetraminos;
    while (curr_index > 0)
    {
        int random_index = (random.get_fixed(1) * curr_index).floor_integer();
        curr_index--;

        int temp = bag[curr_index];
        bag[curr_index] = bag[random_index];
        bag[random_index] = temp;
    }
}

Tetramino spawn_next()
{
    if (curr_turn == 0)
    {
        shuffle_bag(tetramino_index_bag);
    }
    int index = tetramino_index_bag[curr_turn];
    bn::sprite_ptr sprite = tetramino_sprite_items[index].create_sprite(0, spawn_y);
    t_col_grid collision_grid = collision_grids[index];
    
    curr_turn++;
    return Tetramino(sprite, collision_grid);
}