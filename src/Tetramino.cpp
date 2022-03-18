#include "Tetramino.h"
#include <bn_regular_bg_map_cell_info.h>
#include <bn_memory.h>
#include <bn_log.h>
#include <bn_assert.h>

Tetramino::Tetramino(bn::sprite_ptr sprite, const bn::array<bool, num_tetramino_cells> collision_grid) : 
    _sprite(sprite), _collision_grid(collision_grid) 
{
}