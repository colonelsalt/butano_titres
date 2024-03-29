#include "RandomBag.h"
#include <bn_display.h>
#include <bn_fixed.h>
#include <bn_array.h>
#include <bn_random.h>
#include <bn_fixed.h>
#include <bn_log.h>
#include "bn_sprite_items_i_tetramino.h"
#include "bn_sprite_items_j_tetramino.h"
#include "bn_sprite_items_l_tetramino.h"
#include "bn_sprite_items_o_tetramino.h"
#include "bn_sprite_items_s_tetramino.h"
#include "bn_sprite_items_t_tetramino.h"
#include "bn_sprite_items_z_tetramino.h"
#include <bn_point.h>

static constexpr bn::array<t_col_grid, 4> i_tetramino_grids =
{{
    {{
        { 0, 0, 0, 0 },
        { 1, 1, 1, 1 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 }
    }},
    {{
        { 0, 0, 1, 0 },
        { 0, 0, 1, 0 },
        { 0, 0, 1, 0 },
        { 0, 0, 1, 0 }
    }},
    {{
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 1, 1, 1, 1 },
        { 0, 0, 0, 0 }
    }},
    {{
        { 0, 1, 0, 0 },
        { 0, 1, 0, 0 },
        { 0, 1, 0, 0 },
        { 0, 1, 0, 0 }
    }}
}};

static constexpr t_col_grid o_grid =
{{
    { 0, 0, 0, 0 },
    { 0, 1, 1, 0 },
    { 0, 1, 1, 0 },
    { 0, 0, 0, 0 }
}};

static constexpr bn::array<t_col_grid, 4> o_tetramino_grids =
{
    o_grid, o_grid, o_grid, o_grid   
};

static constexpr bn::array<t_col_grid, 4> j_tetramino_grids =
{{
    {{
        { 0, 0, 0, 0 },
        { 1, 0, 0, 0 },
        { 1, 1, 1, 0 },
        { 0, 0, 0, 0 }
    }},
    {{
        { 0, 0, 0, 0 },
        { 0, 1, 1, 0 },
        { 0, 1, 0, 0 },
        { 0, 1, 0, 0 }
    }},
    {{
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 1, 1, 1, 0 },
        { 0, 0, 1, 0 }
    }},
    {{
        { 0, 0, 0, 0 },
        { 0, 1, 0, 0 },
        { 0, 1, 0, 0 },
        { 1, 1, 0, 0 }
    }}
}};

static constexpr bn::array<t_col_grid, 4> l_tetramino_grids =
{{
    {{
        { 0, 0, 0, 0 },
        { 0, 0, 1, 0 },
        { 1, 1, 1, 0 },
        { 0, 0, 0, 0 }
    }},
    {{
        { 0, 0, 0, 0 },
        { 0, 1, 0, 0 },
        { 0, 1, 0, 0 },
        { 0, 1, 1, 0 }
    }},
    {{
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 1, 1, 1, 0 },
        { 1, 0, 0, 0 }
    }},
    {{
        { 0, 0, 0, 0 },
        { 1, 1, 0, 0 },
        { 0, 1, 0, 0 },
        { 0, 1, 0, 0 }
    }}
}};

static constexpr bn::array<t_col_grid, 4> s_tetramino_grids =
{{
    {{
        { 0, 0, 0, 0 },
        { 0, 1, 1, 0 },
        { 1, 1, 0, 0 },
        { 0, 0, 0, 0 }
    }},
    {{
        { 0, 0, 0, 0 },
        { 0, 1, 0, 0 },
        { 0, 1, 1, 0 },
        { 0, 0, 1, 0 },
    }},
    {{
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 1, 1, 0 },
        { 1, 1, 0, 0 }
    }},
    {{
        { 0, 0, 0, 0 },
        { 1, 0, 0, 0 },
        { 1, 1, 0, 0 },
        { 0, 1, 0, 0 }
    }}
}};

static constexpr bn::array<t_col_grid, 4> t_tetramino_grids =
{{
    {{
        { 0, 0, 0, 0 },
        { 0, 1, 0, 0 },
        { 1, 1, 1, 0 },
        { 0, 0, 0, 0 }
    }},
    {{
        { 0, 0, 0, 0 },
        { 0, 1, 0, 0 },
        { 0, 1, 1, 0 },
        { 0, 1, 0, 0 }
    }},
    {{
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 1, 1, 1, 0 },
        { 0, 1, 0, 0 }
    }},
    {{
        { 0, 0, 0, 0 },
        { 0, 1, 0, 0 },
        { 1, 1, 0, 0 },
        { 0, 1, 0, 0 }
    }}
}};

static constexpr bn::array<t_col_grid, 4> z_tetramino_grids =
{{
    {{
        { 0, 0, 0, 0 },
        { 1, 1, 0, 0 },
        { 0, 1, 1, 0 },
        { 0, 0, 0, 0 }
    }},
    {{
        { 0, 0, 0, 0 },
        { 0, 0, 1, 0 },
        { 0, 1, 1, 0 },
        { 0, 1, 0, 0 }
    }},
    {{
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 1, 1, 0, 0 },
        { 0, 1, 1, 0 }
    }},
    {{
        { 0, 0, 0, 0 },
        { 0, 1, 0, 0 },
        { 1, 1, 0, 0 },
        { 1, 0, 0, 0 }
    }}
}};

static constexpr bn::array<bn::array<t_col_grid, 4>, num_tetraminos> collision_grids =
{
    i_tetramino_grids,
    j_tetramino_grids,
    l_tetramino_grids,
    o_tetramino_grids,
    s_tetramino_grids,
    t_tetramino_grids,
    z_tetramino_grids
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

const t_wall_kick_list standard_wall_kicks =
{{
    {{
        bn::point(-1, 0), bn::point(-1, -1), bn::point(0, 2), bn::point(-1, 2)
    }},
    {{
        bn::point(1, 0), bn::point(1, 1), bn::point(0, -2), bn::point(1, -2)
    }},
    {{
        bn::point(1, 0), bn::point(1, -1), bn::point(0, 2), bn::point(1, 2)
    }},
    {{
        bn::point(-1, 0), bn::point(-1, 1), bn::point(0, -2), bn::point(1, -2)
    }}
}};

const t_wall_kick_list i_wall_kicks =
{{
    {{
        bn::point(-2, 0), bn::point(1, 0), bn::point(-2, 1), bn::point(1, -2)
    }},
    {{
        bn::point(-1, 0), bn::point(2, 0), bn::point(-1, -2), bn::point(2, -1)
    }},
    {{
        bn::point(2, 0), bn::point(-1, 0), bn::point(2, -1), bn::point(-1, 2)
    }},
    {{
        bn::point(1, 0), bn::point(-2, 0), bn::point(1, 2), bn::point(-2, 1)
    }}
}};

const bn::array<bn::point, 4> dummy_o_wall_kicks =
{
    bn::point(-69, -69), bn::point(-69, -69), bn::point(-69, -69), bn::point(-69, -69)
};

const t_wall_kick_list o_wall_kicks =
{
    dummy_o_wall_kicks, dummy_o_wall_kicks, dummy_o_wall_kicks, dummy_o_wall_kicks
};

constexpr int turns_between_shuffles = 7;
constexpr bn::fixed spawn_y = (-bn::display::height() / 2) + 8;

bn::unique_ptr<DynamicBG> tetramino_bg;
bn::unique_ptr<DynamicBG> ghost_piece_bg;

bn::optional<bn::sprite_ptr> preview_sprite;

bn::random random = bn::random();
int curr_turn = 0;
int curr_level = 1;

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

void init_bgs()
{
    tetramino_bg = bn::unique_ptr<DynamicBG>(new DynamicBG());
    ghost_piece_bg = bn::unique_ptr<DynamicBG>(new DynamicBG());
}

void update_level(int new_level)
{
    curr_level = new_level;
}

Tetramino spawn_next()
{
    int index = tetramino_index_bag[curr_turn];
    bn::array<t_col_grid, 4> col_grids = collision_grids[index];
    curr_turn = (curr_turn + 1) % turns_between_shuffles;
    t_wall_kick_list wall_kicks_list;
    if (index == i_index)
        wall_kicks_list = i_wall_kicks;
    else if (index == o_index)
        wall_kicks_list = o_wall_kicks;
    else
        wall_kicks_list = standard_wall_kicks;

    if (curr_turn == 0)
    {
        shuffle_bag(tetramino_index_bag);
    }
    int next_turn_index = tetramino_index_bag[curr_turn];
    preview_sprite = tetramino_sprite_items[next_turn_index].create_sprite(80, -60);

    return Tetramino(col_grids, tetramino_bg.get(), ghost_piece_bg.get(), wall_kicks_list, curr_level, index);
}