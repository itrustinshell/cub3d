#include "../cub3d.h"
#include <string.h>

/*gli passo un punto per frlo verificare. Se il muro ha attraversato due muri, setta il corrispettivo end_point
da stampare  e ritprna 1 per fare il break.

vedere poi se è megliofare una eventuale verisone che mette piu precisione magari con double
sulla mappa*/
int is_it_passing_between_two_walls(t_c3d *c3d, t_ray *ray, t_point point)
{
    if (c3d->map_fm_file.grid[point.y / TILE_SIZE][((point.x - 1) / TILE_SIZE)] == '1' && c3d->map_fm_file.grid[(point.y + 1) / TILE_SIZE][(point.x / TILE_SIZE)] == '1')
    {
        printf("ma attenzione che le celle affianco sono muri!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
        ray->end_point.x = point.x - 1;
        ray->end_point.y = point.y + 1;
        printf("le cooridnate di impatto sono: %d, %d\n", ray->end_point.x, ray->end_point.y);
        bresenham(c3d, c3d->player.x, c3d->player.y, ray->end_point.x, ray->end_point.y, YELLOW);
        return (1);
    }
    return (0);
}

int is_it_a_wall_for_increment_x(t_c3d *c3d, t_ray *ray)
{
    if (c3d->map_fm_file.grid[ray->end_point_to_check.y / TILE_SIZE][(ray->end_point_to_check.x / TILE_SIZE)] != '1')
    {        
        printf("NO! La cella (%d, %d) NON è un muro\n", ray->end_point_to_check.x / TILE_SIZE, ray->end_point_to_check.y / TILE_SIZE);
        ray->dx = ray->DxTemp; //aggiorno il ray->dx che mi servirà aggiornato per l'iterazione successiva
        ray->sx = ray->SxTemp; //aggiorno per stesso motivo rigo precefente
        ray->end_point.x = ray->end_point_to_check.x; //aggiorno il punto finale
        ray->end_point.y = ray->end_point_to_check.y;
        return (0);
    }
    else
    {
        printf("Si! La cella (%d, %d) è un muro\n", ray->end_point_to_check.x / TILE_SIZE, ray->end_point_to_check.y / TILE_SIZE);
        ray->end_point.x = ray->end_point_to_check.x;
        ray->end_point.y = ray->end_point_to_check.y;
        printf("le cooridnate di impatto sono: %d, %d\n", ray->end_point_to_check.x, ray->end_point_to_check.y);
        bresenham(c3d, c3d->player.x, c3d->player.y, ray->end_point.x, ray->end_point.y, BLUE);
        return (1);
    }
    return (0);
}

int is_it_a_wall_for_increment_y(t_c3d *c3d, t_ray *ray)
{
    if (c3d->map_fm_file.grid[ray->end_point_to_check.y / TILE_SIZE][(ray->end_point_to_check.x / TILE_SIZE)] != '1')
    {
        printf("NO! La cella (%d, %d) NON è un muro\n", ray->end_point_to_check.x / TILE_SIZE, ray->end_point_to_check.y / TILE_SIZE);
        ray->dy = ray->DyTemp; //aggiorno il ray->dx che mi servirà aggiornato per l'iterazione successiva
        ray->sy = ray->SyTemp; 
        ray->end_point.x = ray->end_point_to_check.x;
        ray->end_point.y = ray->end_point_to_check.y;
        return (0);
    }
    else
    {
        printf("Si! La cella (%d, %d) è un muro\n", ray->end_point_to_check.x / TILE_SIZE, ray->end_point_to_check.y / TILE_SIZE);
        ray->end_point.x = ray->end_point_to_check.x;
        ray->end_point.y = ray->end_point_to_check.y;
        bresenham(c3d, c3d->player.x, c3d->player.y, ray->end_point.x, ray->end_point.y, RED);
        return (1);
    }
}

int	is_it_inside_map_perimeter(t_point point, t_c3d *c3d)
{
    //AAA QUESTO è il perimwtro che sondiera proprio la parte interna senza muri
	if (point.x >= TILE_SIZE - 1 && point.x < (c3d->map_fm_file.w * TILE_SIZE - TILE_SIZE) + 1  && point.y >= TILE_SIZE - 1 && point.y < (c3d->map_fm_file.h * TILE_SIZE) - TILE_SIZE + 1)
		return (1);
	else
		return (0);
}