#include "bn_core.h"
#include <bn_fixed.h>
#include <bn_regular_bg_item.h>
#include <bn_regular_bg_ptr.h>
#include "bn_regular_bg_items_bg_grid.h"
#include <bn_log.h>
#include "RandomBag.h"
#include "Grid.h"

constexpr int ticks_between_line_clears = 10;

int main()
{
    bn::core::init();
    BN_LOG("Starting game...");
    
    int line_clear_counter = 0;
    bool is_line_clear_active = false;

    Tetramino active_tetramino = spawn_next();
    bn::regular_bg_ptr bg = bn::regular_bg_items::bg_grid.create_bg(0, 0);
    reset_grid();

    while(true)
    {
        bn::core::update();
        if (is_line_clear_active)
        {
            line_clear_counter++;
            if (line_clear_counter == ticks_between_line_clears)
            {
                is_line_clear_active = false;
                shift_down_cleared_lines();
                active_tetramino = spawn_next();
            }
            else
            {
                continue;
            }
        }

        active_tetramino.update();
        if (active_tetramino.has_collided())
        {
            add_to_grid(active_tetramino);
            
            if (check_for_line_clear())
            {
                is_line_clear_active = true;
                line_clear_counter = 0;
                active_tetramino.hide();
            }
            else
                active_tetramino = spawn_next();
        }
    }
}
