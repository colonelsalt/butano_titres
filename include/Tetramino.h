#pragma once

#include <bn_array.h>
#include <bn_sprite_ptr.h>
#include <bn_optional.h>

constexpr int num_tetramino_cells = 4 * 4;
class Tetramino
{
    private:
        bn::optional<bn::sprite_ptr> _sprite;
        const bn::array<bool, num_tetramino_cells> _collision_grid;

    public:
        Tetramino(bn::sprite_ptr sprite, const bn::array<bool, num_tetramino_cells>);

};
