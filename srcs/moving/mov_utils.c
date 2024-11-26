#include "c3d.h"

t_point tile_reference(t_point point)
{
    t_point tile_reference;

    tile_reference.x = 0;
    tile_reference.y = 0;
    tile_reference.x = (int)(point.x / TILE_SIZE);
    tile_reference.y = (int)(point.y / TILE_SIZE);
    return (tile_reference);
}