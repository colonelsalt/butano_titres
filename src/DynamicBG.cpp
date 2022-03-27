#include "DynamicBG.h"
#include <bn_log.h>
#include "bn_regular_bg_items_tetraminos.h"
#include "bn_regular_bg_map_cell_info.h"
#include <bn_blending.h>

DynamicBG::DynamicBG() : _map_item(_bg_cells[0], bn::size(BG_LENGTH, BG_LENGTH))
{
    bn::regular_bg_item bg_item(bn::regular_bg_items::tetraminos.tiles_item(),
        bn::regular_bg_items::tetraminos.palette_item(), _map_item);
    _bg_ptr = bg_item.create_bg(88, 48);
    _bg_map = _bg_ptr.value().map();
    clear();
}

void DynamicBG::update()
{
    _bg_map.value().reload_cells_ref();
}

void DynamicBG::clear()
{
    bn::memory::clear(BG_LENGTH * BG_LENGTH, _bg_cells[0]);
}

void DynamicBG::add_cell(bn::point pos, int tile_index)
{
    bn::regular_bg_map_cell& cell = _bg_cells[_map_item.cell_index(pos.x(), pos.y())];
    bn::regular_bg_map_cell_info cell_info(cell);

    cell_info.set_tile_index(tile_index);
    cell = cell_info.cell();
}

void DynamicBG::copy_cell_from_above(bn::point pos, int offset)
{
    bn::regular_bg_map_cell& cell_above = _bg_cells[_map_item.cell_index(pos.x(), pos.y() - offset)];
    bn::regular_bg_map_cell_info cell_above_info(cell_above);
    add_cell(pos, cell_above_info.tile_index() % 8);
}

void DynamicBG::set_visible(bool visible)
{
    _bg_ptr.value().set_visible(visible);
}

void DynamicBG::set_priority(int priority)
{
    _bg_ptr.value().set_priority(priority);
}

void DynamicBG::set_alpha(bn::fixed alpha)
{
    _bg_ptr.value().set_blending_enabled(true);
    bn::blending::set_fade_alpha(alpha);
}