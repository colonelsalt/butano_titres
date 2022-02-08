#include "bn_core.h"
#include <bn_fixed.h>
#include <bn_regular_bg_item.h>
#include <bn_regular_bg_ptr.h>
#include "bn_regular_bg_items_bg_grid.h"

int main()
{
    bn::core::init();

    bn::regular_bg_ptr bg = bn::regular_bg_items::bg_grid.create_bg(0, 0);

    while(true)
    {
        bn::core::update();
    }
}
