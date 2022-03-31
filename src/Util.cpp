#include "Util.h"

bn::fixed get_ticks_between_moves(int level)
{
    switch (level)
    {
    case 1:
        return 1.0 / 0.01667;
    case 2:
        return 1.0 / 0.021017;
    case 3:
        return 1.0 / 0.026977;
    case 4:
        return 1.0 / 0.035256;
    case 5:
        return 1.0 / 0.04693;
    case 6:
        return 1.0 / 0.06361;
    case 7:
        return 1.0 / 0.0879;
    case 8:
        return 1.0 / 0.1236;
    case 9:
        return 1.0 / 0.1775;
    case 10:
        return 1.0 / 0.2598;
    case 11:
        return 1.0 / 0.388;
    case 12:
        return 1.0 / 0.59;
    case 13:
        return 1.0 / 0.92;
    case 14:
        return 1.0 / 1.46;
    case 15:
        return 1.0 / 2.36;
    case 16:
        return 1.0 / 3.91;
    case 17:
        return 1.0 / 6.61;
    case 18:
        return 1.0 / 11.43;
    case 19:
        return 1.0 / 20;
    default:
        BN_UNREACHABLE();
    }
}