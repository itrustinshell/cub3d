#include "../cub3d.h"
#include <string.h>

/*gli passo un punto per frlo verificare. Se il muro ha attraversato due muri, setta il corrispettivo end_point
da stampare  e ritprna 1 per fare il break.

vedere poi se è megliofare una eventuale verisone che mette piu precisione magari con double
sulla mappa*/
int is_it_passing_between_two_walls(t_c3d *c3d, t_ray *ray, char **map_grid, t_point point_to_verify)
{
    if (map_grid[(int)point_to_verify.y / TILE_SIZE][(((int)point_to_verify.x - 1) / TILE_SIZE)] == '1' && c3d->map_fm_file.grid[((int)point_to_verify.y + 1) / TILE_SIZE][((int)point_to_verify.x / TILE_SIZE)] == '1')
    {
        printf("Attenzione sei passato tra due muri !!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
        point_to_verify.x = point_to_verify.x - 1;
        point_to_verify.y = point_to_verify.y + 1;
        printf("le cooridnate di impatto sono: %d, %d\n", (int)ray->end_point.x, (int)ray->end_point.y);
        bresenham(c3d, c3d->player.position.x, c3d->player.position.y, point_to_verify.x, point_to_verify.y, YELLOW);
        return (1);
    }
    return (0);
}

int is_it_a_wall(char **map_grid, t_point point_to_verify, t_c3d *c3d)
{
    t_c3d *ciao;
    ciao = c3d;

    if (map_grid[(int)point_to_verify.y / TILE_SIZE][(int)point_to_verify.x / TILE_SIZE] == '1')
    {
        printf("Si! La cella (%f, %f) è un muro\n", point_to_verify.x / TILE_SIZE, point_to_verify.y / TILE_SIZE);
        return (1);
    }
    else
    { 
        printf("NO! La cella (%f, %f) NON è un muro\n", point_to_verify.x / TILE_SIZE, point_to_verify.y / TILE_SIZE);
        return (0);
    }
    return (1);
}

int	is_it_inside_map_perimeter(t_point point, t_c3d *c3d) //AAA QUESTO è il perimwtro che sondiera proprio la parte interna senza muri
{
	if (point.x >= TILE_SIZE - 1 && point.x < (c3d->map_fm_file.w * TILE_SIZE - TILE_SIZE) + 1  && point.y >= TILE_SIZE - 1 && point.y < (c3d->map_fm_file.h * TILE_SIZE) - TILE_SIZE + 1)
		return (1);
	else
		return (0);
}