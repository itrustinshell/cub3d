#include "../c3d.h"

int is_it_a_wall(t_point point_to_verify, char **map_grid)
{
    if (map_grid[(int)point_to_verify.y / TILE_SIZE][(int)point_to_verify.x / TILE_SIZE] == IS_A_WALL)
        return (IT_IS_A_WALL);
    else
        return (IT_IS_NOT_A_WALL);
    return (IT_IS_A_WALL);
}

int	is_it_inside_map_perimeter(t_point point_to_verify, t_dimension map_dimension) //AAA QUESTO è il perimwtro che sondiera proprio la parte interna senza muri
{
	if (point_to_verify.x >= TILE_SIZE && point_to_verify.x < (map_dimension.width * TILE_SIZE - TILE_SIZE)  && point_to_verify.y >= TILE_SIZE && point_to_verify.y < (map_dimension.heigth * TILE_SIZE) - TILE_SIZE)
		return (INSIDE_PERIMETER);
	return (OUTSIDE_PERIMETER);
}
