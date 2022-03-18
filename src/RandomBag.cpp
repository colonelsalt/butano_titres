#include "RandomBag.h"
#include <bn_display.h>
#include <bn_fixed.h>
#include <bn_vector.h>
#include <bn_array.h>
#include "bn_sprite_items_i_tetramino.h"
#include "bn_sprite_items_j_tetramino.h"
#include "bn_sprite_items_l_tetramino.h"
#include "bn_sprite_items_o_tetramino.h"
#include "bn_sprite_items_s_tetramino.h"
#include "bn_sprite_items_t_tetramino.h"
#include "bn_sprite_items_z_tetramino.h"

static constexpr bn::array<bool, num_tetramino_cells> i_tetramino_grid =
{
    0, 0, 0, 0,
    1, 1, 1, 1,
    0, 0, 0, 0,
    0, 0, 0, 0
};

static constexpr bn::array<bool, num_tetramino_cells> o_tetramino_grid =
{
    0, 0, 0, 0,
    0, 1, 1, 0,
    0, 1, 1, 0,
    0, 0, 0, 0
};

static constexpr bn::array<bool, num_tetramino_cells> j_tetramino_grid =
{
    0, 1, 0, 0,
    0, 1, 1, 1,
    0, 0, 0, 0,
    0, 0, 0, 0
};

static constexpr bn::array<bool, num_tetramino_cells> l_tetramino_grid =
{
    0, 0, 0, 1,
    0, 1, 1, 1,
    0, 0, 0, 0,
    0, 0, 0, 0
};

static constexpr bn::array<bool, num_tetramino_cells> s_tetramino_grid =
{
    0, 0, 1, 1,
    0, 1, 1, 0,
    0, 0, 0, 0,
    0, 0, 0, 0
};

static constexpr bn::array<bool, num_tetramino_cells> t_tetramino_grid =
{
    0, 0, 1, 0,
    0, 1, 1, 1,
    0, 0, 0, 0,
    0, 0, 0, 0
};

static constexpr bn::array<bool, num_tetramino_cells> z_tetramino_grid =
{
    0, 1, 1, 0,
    0, 0, 1, 1,
    0, 0, 0, 0,
    0, 0, 0, 0
};

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

//Tetramino active_tetramino;
constexpr bn::fixed spawn_y = (-bn::display::height() / 2) + 16;

Tetramino spawn_next()
{
    int index = 0;
    bn::sprite_ptr sprite = tetramino_sprite_items[index].create_sprite(0, spawn_y);
    return Tetramino(sprite, i_tetramino_grid);
}