#include "../cub3d.h"
#include <string.h>

/*
Legenda:
deltax = delta_x (is the distance from prlayer.x to the chosen TILE'side)
deltay = delta_y
distx = path_for_delta_x (is the hypotenus calculated for a particular delta_x)
disty = path_for_delta_y
*/

/*
if you want to print this distance, then insert the following code:
// int x1 = c3d->player.x + fabs(distance_for_delta_x) * cos(c3d->player.alpha_direction);
// int y1 = c3d->player.y + fabs(distance_for_delta_x) * sin(c3d->player.alpha_direction);
// bresenham(c3d, c3d->player.x, c3d->player.y , x1, y1, RED);
*/
double	dist_along_ray_in_movement_x(t_c3d *c3d, t_ray *ray, double alpha)
{
	if (alpha == (M_PI / 2) || alpha == (3 * M_PI / 2))
		ray->path_for_delta_x = ray->delta_y / sin(alpha);
	else
		ray->path_for_delta_x = ray->delta_x / cos(alpha);
	if (fabs(ray->path_for_delta_x) > (c3d->map_fm_file.w * TILE_SIZE))
		ray->path_for_delta_x = c3d->map_fm_file.w * TILE_SIZE; //qui ho ridotto molto perchè erano lunghezze enormi man mano che ci si avvicinava a pi/2 ma vedi ora come gestire
	printf("ipotenusa tramite delta_x: %f\n", ray->path_for_delta_x);
	// int x1 = c3d->player.x + fabs(ray->path_for_delta_x) * cos(c3d->player.alpha_direction);
	// int y1 = c3d->player.y + fabs(ray->path_for_delta_x) * sin(c3d->player.alpha_direction);
	// bresenham(c3d, c3d->player.x, c3d->player.y , x1, y1, RED);
	return (ray->path_for_delta_x);
}

/*
if you want to print this distance, then insert the following code:
// int x2 = c3d->player.x + fabs(distance_for_delta_y) * cos(c3d->player.alpha_direction);
// int y2 = c3d->player.y + fabs(distance_for_delta_y) * sin(c3d->player.alpha_direction);
// bresenham(c3d, c3d->player.x, c3d->player.y , x2, y2, WHITE);
*/
double	dist_along_ray_in_movement_y(t_c3d *c3d,  t_ray *ray, double alpha)
{
	if (alpha == (M_PI) || alpha == (2 * M_PI) || alpha == (0))
         ray->path_for_delta_y = ray->delta_x / cos(alpha);
	else
         ray->path_for_delta_y = ray->delta_y / sin(alpha);
	if (fabs( ray->path_for_delta_y) > (c3d->map_fm_file.h * TILE_SIZE))
         ray->path_for_delta_y = c3d->map_fm_file.h * TILE_SIZE; //qui ho ridotto molto perchè erano lunghezze enormi man mano che ci si avvicinava a pi/2 ma vedi ora come gestire
    printf("ipotenusa tramite delta_y: %f\n",  ray->path_for_delta_y);
	
//  int x2 = c3d->player.x + fabs(ray->path_for_delta_y) * cos(c3d->player.alpha_direction);
//     int y2 = c3d->player.y + fabs(ray->path_for_delta_y) * sin(c3d->player.alpha_direction);
//  bresenham(c3d, c3d->player.x, c3d->player.y , x2, y2, WHITE);
    return ( ray->path_for_delta_y);
}

void calculate_delta_x(t_c3d *c3d, t_ray *ray)
{
    if (strcmp(ray->cardinal_direction, "E") == 0)
        ray->delta_x = fabs(ray->first_side_point.x - c3d->player.x); 
    else if (strcmp(ray->cardinal_direction, "NE") == 0 )
        ray->delta_x = fabs(ray->first_side_point.x - c3d->player.x); 
    else if (strcmp(ray->cardinal_direction, "N") == 0 )
        ray->delta_x = fabs(ray->first_side_point.x - c3d->player.x); //VERIFICA SE VA BENE dovrebbe essere indifferente se riferisce a lato delta_x o sx
    else if (strcmp(ray->cardinal_direction, "NW") == 0 )
        ray->delta_x = fabs(ray->first_side_point.x - c3d->player.x - 1);
    else if (strcmp(ray->cardinal_direction, "W") == 0 )
        ray->delta_x = fabs(ray->first_side_point.x - c3d->player.x - 1);
    else if (strcmp(ray->cardinal_direction, "SW") == 0 )
        ray->delta_x = fabs(ray->first_side_point.x - c3d->player.x - 1);
    else if (strcmp(ray->cardinal_direction, "S") == 0 )
        ray->delta_x = fabs(ray->first_side_point.x - c3d->player.x - 1);
    else if (strcmp(ray->cardinal_direction, "SE") == 0 )
        ray->delta_x = fabs(ray->first_side_point.x - c3d->player.x - 1);
}

void calculate_delta_y(t_c3d *c3d, t_ray *ray)
{
    if (strcmp(ray->cardinal_direction, "E") == 0)
        ray->delta_y = fabs(c3d->player.y - ray->first_side_point.y + 1);
    if (strcmp(ray->cardinal_direction, "NE") == 0)
        ray->delta_y = fabs(c3d->player.y - ray->first_side_point.y + 1); 
    else if (strcmp(ray->cardinal_direction, "N") == 0 )
        ray->delta_y = fabs(c3d->player.y - ray->first_side_point.y + 1); 
    else if (strcmp(ray->cardinal_direction, "NW") == 0 )
        ray->delta_y = fabs(c3d->player.y - ray->first_side_point.y + 1);
    else if (strcmp(ray->cardinal_direction, "W") == 0 )
        ray->delta_y = fabs(c3d->player.y - ray->first_side_point.y + 1); //dovrebbe essere indifferente se su o giu
    else if (strcmp(ray->cardinal_direction, "SW") == 0 )
        ray->delta_y = fabs(c3d->player.y - ray->first_side_point.y); 
    else if (strcmp(ray->cardinal_direction, "S") == 0 )
        ray->delta_y = fabs(c3d->player.y - ray->first_side_point.y);
    else if (strcmp(ray->cardinal_direction, "SE") == 0 )
        ray->delta_y = fabs(c3d->player.y - ray->first_side_point.y); 
}

