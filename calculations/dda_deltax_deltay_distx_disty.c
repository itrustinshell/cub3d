#include "../cub3d.h"
#include <string.h>

/*
Legenda:
deltax = dx (is the distance from prlayer.x to the chosen TILE'side)
deltay = dy
distx = sx (is the hypotenus calculated for a particular dx)
disty = sy
*/

/*
if you want to print this distance, then insert the following code:
// int x1 = c3d->player.x + fabs(distance_for_dx) * cos(c3d->player.alpha_direction);
// int y1 = c3d->player.y + fabs(distance_for_dx) * sin(c3d->player.alpha_direction);
// bresenham(c3d, c3d->player.x, c3d->player.y , x1, y1, RED);
*/
double	calculate_sx(t_c3d *c3d, t_ray *ray, double alpha)
{
	if (alpha == (M_PI / 2) || alpha == (3 * M_PI / 2))
		ray->sx = ray->dy / sin(alpha);
	else
		ray->sx = ray->dx / cos(alpha);
	if (fabs(ray->sx) > (c3d->map_fm_file.w * TILE_SIZE))
		ray->sx = c3d->map_fm_file.w * TILE_SIZE; //qui ho ridotto molto perchè erano lunghezze enormi man mano che ci si avvicinava a pi/2 ma vedi ora come gestire
	printf("ipotenusa tramite dx: %f\n", fabs(ray->sx));
	// int x1 = c3d->player.x + fabs(ray->sx) * cos(c3d->player.alpha_direction);
	// int y1 = c3d->player.y + fabs(ray->sx) * sin(c3d->player.alpha_direction);
	// bresenham(c3d, c3d->player.x, c3d->player.y , x1, y1, RED);
	return (fabs(ray->sx));
}

/*
if you want to print this distance, then insert the following code:
// int x2 = c3d->player.x + fabs(distance_for_dy) * cos(c3d->player.alpha_direction);
// int y2 = c3d->player.y + fabs(distance_for_dy) * sin(c3d->player.alpha_direction);
// bresenham(c3d, c3d->player.x, c3d->player.y , x2, y2, WHITE);
*/
double	calculate_sy(t_c3d *c3d,  t_ray *ray, double alpha)
{
	if (alpha == (M_PI) || alpha == (2 * M_PI) || alpha == (0))
         ray->sy = ray->dx / cos(alpha);
	else
         ray->sy = ray->dy / sin(alpha);
	if (fabs( ray->sy) > (c3d->map_fm_file.h * TILE_SIZE))
         ray->sy = c3d->map_fm_file.h * TILE_SIZE; //qui ho ridotto molto perchè erano lunghezze enormi man mano che ci si avvicinava a pi/2 ma vedi ora come gestire
    printf("ipotenusa tramite dy: %f\n",  fabs(ray->sy));
	
//  int x2 = c3d->player.x + fabs(ray->sy) * cos(c3d->player.alpha_direction);
//     int y2 = c3d->player.y + fabs(ray->sy) * sin(c3d->player.alpha_direction);
//  bresenham(c3d, c3d->player.x, c3d->player.y , x2, y2, WHITE);
    return (fabs(ray->sy));
}

void calculate_dx(t_c3d *c3d, t_ray *ray)
{
    if (strcmp(ray->cardinal_direction, "E") == 0)
        ray->dx = fabs(ray->first_impact_point.x - c3d->player.x); 
    else if (strcmp(ray->cardinal_direction, "NE") == 0 )
        ray->dx = fabs(ray->first_impact_point.x - c3d->player.x); 
    else if (strcmp(ray->cardinal_direction, "N") == 0 )
        ray->dx = fabs(ray->first_impact_point.x - c3d->player.x); //VERIFICA SE VA BENE dovrebbe essere indifferente se riferisce a lato dx o sx
    else if (strcmp(ray->cardinal_direction, "NW") == 0 )
        ray->dx = fabs(ray->first_impact_point.x - c3d->player.x - 1);
    else if (strcmp(ray->cardinal_direction, "W") == 0 )
        ray->dx = fabs(ray->first_impact_point.x - c3d->player.x - 1);
    else if (strcmp(ray->cardinal_direction, "SW") == 0 )
        ray->dx = fabs(ray->first_impact_point.x - c3d->player.x - 1);
    else if (strcmp(ray->cardinal_direction, "S") == 0 )
        ray->dx = fabs(ray->first_impact_point.x - c3d->player.x - 1);
    else if (strcmp(ray->cardinal_direction, "SE") == 0 )
        ray->dx = fabs(ray->first_impact_point.x - c3d->player.x - 1);
}

void calculate_dy(t_c3d *c3d, t_ray *ray)
{
    if (strcmp(ray->cardinal_direction, "E") == 0)
        ray->dy = fabs(c3d->player.y - ray->first_impact_point.y + 1);
    if (strcmp(ray->cardinal_direction, "NE") == 0)
        ray->dy = fabs(c3d->player.y - ray->first_impact_point.y + 1); 
    else if (strcmp(ray->cardinal_direction, "N") == 0 )
        ray->dy = fabs(c3d->player.y - ray->first_impact_point.y + 1); 
    else if (strcmp(ray->cardinal_direction, "NW") == 0 )
        ray->dy = fabs(c3d->player.y - ray->first_impact_point.y + 1);
    else if (strcmp(ray->cardinal_direction, "W") == 0 )
        ray->dy = fabs(c3d->player.y - ray->first_impact_point.y + 1); //dovrebbe essere indifferente se su o giu
    else if (strcmp(ray->cardinal_direction, "SW") == 0 )
        ray->dy = fabs(c3d->player.y - ray->first_impact_point.y); 
    else if (strcmp(ray->cardinal_direction, "S") == 0 )
        ray->dy = fabs(c3d->player.y - ray->first_impact_point.y);
    else if (strcmp(ray->cardinal_direction, "SE") == 0 )
        ray->dy = fabs(c3d->player.y - ray->first_impact_point.y); 
}

