#include "../cub3d.h"
#include <string.h>

/*
Legenda:
deltax = dx (is the distance from prlayer.x to the chosen TILE'side)
deltay = dy
distx = sx (is the hypotenus calculated for a particular dx)
disty = sy
*/

void calculate_sx_sy(t_c3d *c3d, t_ray *ray, double alpha, char *chose_sx_or_sy)
{
    double distance;
    
    if (strcmp(chose_sx_or_sy, "sx") == 0)
    {
        if (fabs(alpha - M_PI / 2) < EPSILON || fabs(alpha - 3 * M_PI / 2) < EPSILON) //mettiamo il valore assoluto e vediamo se è minore di EPSILON_ Se lo è significa che è prossimo allo zero
            distance = ray->dy / sin(alpha);
        else
            distance = ray->dx / cos(alpha);
        ray->sx = fmin(fabs(distance), c3d->map_fm_file.w * TILE_SIZE); //alla fine restituisvo con fmin confrontando distance con una grandezza scelta da me. Se questa è piu piccola alora me al restituisce perchè altrimenti l'altra sarebbe troppo grande.  fmin mi restituirà il valore piu piccolo.
        printf("ipotenusa tramite dx: %f\n", fabs(ray->sx));
    }
    else
    {
        if (fabs(alpha - M_PI) < EPSILON || fabs(alpha - 2 * M_PI) < EPSILON || fabs(alpha) < EPSILON)
            distance = ray->dx / cos(alpha);
        else
            distance = ray->dy / sin(alpha);

        ray->sy = fmin(fabs(distance), c3d->map_fm_file.h * TILE_SIZE);
        printf("ipotenusa tramite dy: %f\n", fabs(ray->sy));
    }
}


void calculate_dx(t_c3d *c3d, t_ray *ray)
{
    if (strcmp(ray->cardinal_direction, "E") == 0)
        ray->dx = fabs(ray->first_impact_point.x - c3d->player.coordinates.x); 
    else if (strcmp(ray->cardinal_direction, "NE") == 0 )
        ray->dx = fabs(ray->first_impact_point.x - c3d->player.coordinates.x); 
    else if (strcmp(ray->cardinal_direction, "N") == 0 )
        ray->dx = fabs(ray->first_impact_point.x - c3d->player.coordinates.x); //VERIFICA SE VA BENE dovrebbe essere indifferente se riferisce a lato dx o sx
    else if (strcmp(ray->cardinal_direction, "NW") == 0 )
        ray->dx = fabs(ray->first_impact_point.x - c3d->player.coordinates.x - 1);
    else if (strcmp(ray->cardinal_direction, "W") == 0 )
        ray->dx = fabs(ray->first_impact_point.x - c3d->player.coordinates.x - 1);
    else if (strcmp(ray->cardinal_direction, "SW") == 0 )
        ray->dx = fabs(ray->first_impact_point.x - c3d->player.coordinates.x - 1);
    else if (strcmp(ray->cardinal_direction, "S") == 0 )
        ray->dx = fabs(ray->first_impact_point.x - c3d->player.coordinates.x - 1);
    else if (strcmp(ray->cardinal_direction, "SE") == 0 )
        ray->dx = fabs(ray->first_impact_point.x - c3d->player.coordinates.x - 1);
}

void calculate_dy(t_c3d *c3d, t_ray *ray)
{
    if (strcmp(ray->cardinal_direction, "E") == 0)
        ray->dy = fabs(c3d->player.coordinates.y - ray->first_impact_point.y + 1);
    if (strcmp(ray->cardinal_direction, "NE") == 0)
        ray->dy = fabs(c3d->player.coordinates.y - ray->first_impact_point.y + 1); 
    else if (strcmp(ray->cardinal_direction, "N") == 0 )
        ray->dy = fabs(c3d->player.coordinates.y - ray->first_impact_point.y + 1); 
    else if (strcmp(ray->cardinal_direction, "NW") == 0 )
        ray->dy = fabs(c3d->player.coordinates.y - ray->first_impact_point.y + 1);
    else if (strcmp(ray->cardinal_direction, "W") == 0 )
        ray->dy = fabs(c3d->player.coordinates.y - ray->first_impact_point.y + 1); //dovrebbe essere indifferente se su o giu
    else if (strcmp(ray->cardinal_direction, "SW") == 0 )
        ray->dy = fabs(c3d->player.coordinates.y - ray->first_impact_point.y); 
    else if (strcmp(ray->cardinal_direction, "S") == 0 )
        ray->dy = fabs(c3d->player.coordinates.y - ray->first_impact_point.y);
    else if (strcmp(ray->cardinal_direction, "SE") == 0 )
        ray->dy = fabs(c3d->player.coordinates.y - ray->first_impact_point.y); 
}

void calculate_dx_dy(t_c3d *c3d, t_ray *ray, char *chose_dx_or_dy)
{
    if (strcmp(chose_dx_or_dy, "dx") == 0)
        calculate_dx(c3d, ray);
    else
        calculate_dy(c3d, ray);
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
