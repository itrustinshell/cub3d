#include "../cub3d.h"
#include <string.h>

/*
Legenda:
deltax = dx (is the distance from prlayer.x to the chosen TILE'side)
deltay = dy
distx = sx (is the hypotenus calculated for a particular dx)
disty = sy
*/

void calculate_initial_deltaX(t_point initial_side_point, t_c3d *c3d, t_ray *ray)
{
    if (strcmp(ray->cardinal_direction, "E") == 0)
        ray->delta.x = fabs(initial_side_point.x - c3d->player.position.x); 
    else if (strcmp(ray->cardinal_direction, "NE") == 0 )
        ray->delta.x = fabs(initial_side_point.x - c3d->player.position.x); 
    else if (strcmp(ray->cardinal_direction, "N") == 0 )
        ray->delta.x = fabs(initial_side_point.x - c3d->player.position.x); //VERIFICA SE VA BENE dovrebbe essere indifferente se riferisce a lato dx o sx
    else if (strcmp(ray->cardinal_direction, "NW") == 0 )
        ray->delta.x = fabs(initial_side_point.x - c3d->player.position.x - 1);
    else if (strcmp(ray->cardinal_direction, "W") == 0 )
        ray->delta.x = fabs(initial_side_point.x - c3d->player.position.x - 1);
    else if (strcmp(ray->cardinal_direction, "SW") == 0 )
        ray->delta.x = fabs(initial_side_point.x - c3d->player.position.x - 1);
    else if (strcmp(ray->cardinal_direction, "S") == 0 )
        ray->delta.x = fabs(initial_side_point.x - c3d->player.position.x - 1);
    else if (strcmp(ray->cardinal_direction, "SE") == 0 )
        ray->delta.x = fabs(initial_side_point.x - c3d->player.position.x - 1);
}

void calculate_initial_deltaY(t_point initial_side_point, t_c3d *c3d, t_ray *ray)
{
    if (strcmp(ray->cardinal_direction, "E") == 0)
        ray->delta.y = fabs(c3d->player.position.y - initial_side_point.y + 1);
    if (strcmp(ray->cardinal_direction, "NE") == 0)
        ray->delta.y = fabs(c3d->player.position.y - initial_side_point.y + 1); 
    else if (strcmp(ray->cardinal_direction, "N") == 0 )
        ray->delta.y = fabs(c3d->player.position.y - initial_side_point.y + 1); 
    else if (strcmp(ray->cardinal_direction, "NW") == 0 )
        ray->delta.y = fabs(c3d->player.position.y - initial_side_point.y + 1);
    else if (strcmp(ray->cardinal_direction, "W") == 0 )
        ray->delta.y = fabs(c3d->player.position.y - initial_side_point.y + 1); //dovrebbe essere indifferente se su o giu
    else if (strcmp(ray->cardinal_direction, "SW") == 0 )
        ray->delta.y = fabs(c3d->player.position.y - initial_side_point.y); 
    else if (strcmp(ray->cardinal_direction, "S") == 0 )
        ray->delta.y = fabs(c3d->player.position.y - initial_side_point.y);
    else if (strcmp(ray->cardinal_direction, "SE") == 0 )
        ray->delta.y = fabs(c3d->player.position.y - initial_side_point.y); 
}

void calculate_initial_delta(t_point first_side_point, t_c3d *c3d, t_ray *ray, int chose_delta)
{
    if (chose_delta == DELTA_X)
        calculate_initial_deltaX(first_side_point, c3d, ray);
    else
        calculate_initial_deltaY(first_side_point, c3d, ray);
}

/* //# NOTA_4
if you want to print this distance, then insert the following code:
// int x1 = c3d->player.coordinates.x + fabs(distance_for_dx) * cos(c3d->player.alpha_direction);
// int y1 = c3d->player.coordinates.y + fabs(distance_for_dx) * sin(c3d->player.alpha_direction);
// bresenham(c3d, c3d->player.coordinates.x, c3d->player.coordinates.y , x1, y1, RED);
*/

/* NOTA_5
if you want to print this distance, then insert the following code:
// int x2 = c3d->player.coordinates.x + fabs(distance_for_dy) * cos(c3d->player.alpha_direction);
// int y2 = c3d->player.coordinates.y + fabs(distance_for_dy) * sin(c3d->player.alpha_direction);
// bresenham(c3d, c3d->player.coordinates.x, c3d->player.coordinates.y , x2, y2, WHITE);
*/
