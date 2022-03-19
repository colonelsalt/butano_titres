#include "bn_core.h"
#include <bn_fixed.h>
#include <bn_regular_bg_item.h>
#include <bn_regular_bg_ptr.h>
#include "bn_regular_bg_items_bg_grid.h"
#include <bn_log.h>
#include "RandomBag.h"


int main()
{
    bn::core::init();
    BN_LOG("Starting game...");
    Tetramino active_tetramino = spawn_next();
    bn::regular_bg_ptr bg = bn::regular_bg_items::bg_grid.create_bg(0, 0);

    while(true)
    {
        bn::core::update();
        active_tetramino.update();
    }
}
