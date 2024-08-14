#include "../cub3d.h"
#include <string.h>

/*
Legenda:
deltax = dx (is the distance from prlayer.x to the chosen TILE'side)
deltay = dy
distx = sx (is the hypotenus calculated for a particular dx)
disty = sy
*/

double calculate_path(int map_length, double deltaX, double deltaY, double alpha, int chose_path)
{
    double path;

    path = 0;
    if (chose_path == PATH_X)
    {
        if (fabs(alpha - M_PI / 2) < EPSILON || fabs(alpha - 3 * M_PI / 2) < EPSILON) //mettiamo il valore assoluto e vediamo se è minore di EPSILON_ Se lo è significa che è prossimo allo zero
            path = deltaY / sin(alpha);
        else
            path = deltaX / cos(alpha);printf("ipotenusa tramite dx: %f\n", fabs(path));
    }
    else
    {
        if (fabs(alpha - M_PI) < EPSILON || fabs(alpha - 2 * M_PI) < EPSILON || fabs(alpha) < EPSILON)
            path = deltaX / cos(alpha);
        else
            path = deltaY / sin(alpha);printf("ipotenusa tramite dy: %f\n", fabs(path));
    }
    path = fmin(fabs(path), map_length * TILE_SIZE);
    return (fabs(path));
}

void calculate_initial_dx(t_point initial_side_point, t_c3d *c3d, t_ray *ray)
{
    if (strcmp(ray->cardinal_direction, "E") == 0)
        ray->dx = fabs(initial_side_point.x - c3d->player.position.x); 
    else if (strcmp(ray->cardinal_direction, "NE") == 0 )
        ray->dx = fabs(initial_side_point.x - c3d->player.position.x); 
    else if (strcmp(ray->cardinal_direction, "N") == 0 )
        ray->dx = fabs(initial_side_point.x - c3d->player.position.x); //VERIFICA SE VA BENE dovrebbe essere indifferente se riferisce a lato dx o sx
    else if (strcmp(ray->cardinal_direction, "NW") == 0 )
        ray->dx = fabs(initial_side_point.x - c3d->player.position.x - 1);
    else if (strcmp(ray->cardinal_direction, "W") == 0 )
        ray->dx = fabs(initial_side_point.x - c3d->player.position.x - 1);
    else if (strcmp(ray->cardinal_direction, "SW") == 0 )
        ray->dx = fabs(initial_side_point.x - c3d->player.position.x - 1);
    else if (strcmp(ray->cardinal_direction, "S") == 0 )
        ray->dx = fabs(initial_side_point.x - c3d->player.position.x - 1);
    else if (strcmp(ray->cardinal_direction, "SE") == 0 )
        ray->dx = fabs(initial_side_point.x - c3d->player.position.x - 1);
}

void calculate_initial_dy(t_point initial_side_point, t_c3d *c3d, t_ray *ray)
{
    if (strcmp(ray->cardinal_direction, "E") == 0)
        ray->dy = fabs(c3d->player.position.y - initial_side_point.y + 1);
    if (strcmp(ray->cardinal_direction, "NE") == 0)
        ray->dy = fabs(c3d->player.position.y - initial_side_point.y + 1); 
    else if (strcmp(ray->cardinal_direction, "N") == 0 )
        ray->dy = fabs(c3d->player.position.y - initial_side_point.y + 1); 
    else if (strcmp(ray->cardinal_direction, "NW") == 0 )
        ray->dy = fabs(c3d->player.position.y - initial_side_point.y + 1);
    else if (strcmp(ray->cardinal_direction, "W") == 0 )
        ray->dy = fabs(c3d->player.position.y - initial_side_point.y + 1); //dovrebbe essere indifferente se su o giu
    else if (strcmp(ray->cardinal_direction, "SW") == 0 )
        ray->dy = fabs(c3d->player.position.y - initial_side_point.y); 
    else if (strcmp(ray->cardinal_direction, "S") == 0 )
        ray->dy = fabs(c3d->player.position.y - initial_side_point.y);
    else if (strcmp(ray->cardinal_direction, "SE") == 0 )
        ray->dy = fabs(c3d->player.position.y - initial_side_point.y); 
}

void calculate_initial_dx_dy(t_point first_side_point, t_c3d *c3d, t_ray *ray, char *chose_dx_or_dy)
{
    if (strcmp(chose_dx_or_dy, "dx") == 0)
        calculate_initial_dx(first_side_point, c3d, ray);
    else
        calculate_initial_dy(first_side_point, c3d, ray);
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
