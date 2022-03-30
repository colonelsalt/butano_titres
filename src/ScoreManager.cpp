#include "ScoreManager.h"
#include <bn_sprite_text_generator.h>
#include <bn_fixed_point.h>
#include <bn_string_view.h>
#include <bn_format.h>
#include <bn_sprite_ptr.h>
#include "common_variable_8x16_sprite_font.h"
#include "RandomBag.h"

bn::vector<bn::sprite_ptr, 32> static_text_sprites;
bn::vector<bn::sprite_ptr, 32> dynamic_text_sprites;
bn::sprite_text_generator static_text_generator(common::variable_8x16_sprite_font);
bn::sprite_text_generator dynamic_text_generator(common::variable_8x16_sprite_font);
int level = 1;
int score = 0;
int lines = 0;
constexpr bn::fixed_point score_text_pos(60, -40);
constexpr bn::fixed_point score_number_pos(77, -20);
constexpr bn::fixed_point level_text_pos(60, 0);
constexpr bn::fixed_point level_number_pos(77, 20);

void update_score_text()
{
    dynamic_text_sprites.clear();
    
    bn::string score_text = bn::format<16>("{}", score);
    dynamic_text_generator.set_center_alignment();
    dynamic_text_generator.generate(score_number_pos, score_text, dynamic_text_sprites);

    bn::string level_text = bn::format<16>("{}", level);
    dynamic_text_generator.generate(level_number_pos, level_text, dynamic_text_sprites);
}

void update_level()
{
    if (lines % 10 == 0 && lines > 0 && level < 19)
    {
        level++;
        update_score_text();
    }
}

void reset_score()
{
    level = 1;
    score = 0;
    lines = 0;
    static_text_sprites.clear();
    dynamic_text_sprites.clear();
    static_text_generator.set_left_alignment();
    static_text_generator.generate(score_text_pos, "Score:", static_text_sprites);
    static_text_generator.generate(level_text_pos, "Level:", static_text_sprites);
    update_score_text();
}

void increment_score_line_clear(int num_line_clears)
{
    switch (num_line_clears)
    {
    case 1:
        score += 100 * level;
        break;
    case 2:
        score += 300 * level;
        break;
    case 3:
        score += 500 * level;
        break;
    case 4:
        score += 800 * level;
        break;
    default:
        break;
    }
    lines += num_line_clears;
    update_level();
    update_score_text();
}

void increment_score_on_commit(int num_soft_drop_cells, int num_hard_drop_cells)
{
    score += num_soft_drop_cells;
    score += num_hard_drop_cells * 2;
    update_score_text();
}

void game_over()
{

}