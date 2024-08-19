#include "../cub3d.h"

int is_it_a_wall(t_point point_to_verify, char **map_grid)
{
    if (map_grid[(int)point_to_verify.y / TILE_SIZE][(int)point_to_verify.x / TILE_SIZE] == IS_A_WALL)
    {
        printf("Si! La cella (%f, %f) è un muro\n", point_to_verify.x / TILE_SIZE, point_to_verify.y / TILE_SIZE);
        return (IT_IS_A_WALL);
    }
    else
    { 
        printf("NO! La cella (%f, %f) NON è un muro\n", point_to_verify.x / TILE_SIZE, point_to_verify.y / TILE_SIZE);
        return (IT_IS_NOT_A_WALL);
    }
    return (IT_IS_A_WALL);
}




int	is_it_inside_map_perimeter(t_point point, t_c3d *c3d) //AAA QUESTO è il perimwtro che sondiera proprio la parte interna senza muri
{
	if (point.x >= TILE_SIZE - 1 && point.x < (c3d->map_fm_file.w * TILE_SIZE - TILE_SIZE) + 1  && point.y >= TILE_SIZE - 1 && point.y < (c3d->map_fm_file.h * TILE_SIZE) - TILE_SIZE + 1)
		return (1);
	else
		return (0);
}

/*this function checks if even the other point belongs to a wall.
To be executed it means that the first point for sure belongs to a wall.
It set th first_impact_point*/
t_point	check_if_are_both_walls_and_set_firstSidePoint(t_point point_of_a_wall, t_point point_to_verify, char **map_grid, t_ray *ray, t_c3d *c3d) 
{
    t_c3d *ciao;
    ciao = c3d;
		if (is_it_a_wall(point_to_verify, map_grid)) //allora vedi se anche quello con sy è di un muro
		{
			//per stare qui allora entrmabi sono due punti che incontrano muri quindi
			if (fabs(ray->path.x) <= fabs(ray->path.y)) //qui gestisci anche un uguale occhio // se sx + piu piccolo allora ritorni il punto su sx
				return (point_of_a_wall);
			else
				return (point_to_verify); //altrimenti ritorni quell'altro
		}
		else
			return (point_of_a_wall); //se sei qui significa che solo il punto con sx era quello di impatto e quindi ritornaleo
		return (point_of_a_wall);
}   