#include "../cub3d.h"
#include <string.h>

/*this function chose the side of the tile, and consequently the point 
according to angle_direction. This is useful to get the later the distance
dx and dy from that side.
*/
t_point chose_side_point(t_c3d *c3d, t_ray *ray)
{
    t_point side_point;

    side_point.x = 0;
    side_point.y = 0;
    if (strcmp(ray->cardinal_direction, "NE") == 0 || strcmp(ray->cardinal_direction, "E") == 0)
    {
        side_point.x = (c3d->player.tile_x + 1) * TILE_SIZE;
        side_point.y = c3d->player.tile_y * TILE_SIZE;
    }
    else if (strcmp(ray->cardinal_direction, "NW") == 0 || strcmp(ray->cardinal_direction, "W") == 0 || strcmp(ray->cardinal_direction, "N") == 0)
    {
        side_point.x = c3d->player.tile_x * TILE_SIZE;
        side_point.y = c3d->player.tile_y * TILE_SIZE;
    }
    else if (strcmp(ray->cardinal_direction, "SE") == 0)
    {
        side_point.x = (c3d->player.tile_x + 1) * TILE_SIZE;
        side_point.y = (c3d->player.tile_y + 1) * TILE_SIZE;
    }
    else if (strcmp(ray->cardinal_direction, "SW") == 0 || strcmp(ray->cardinal_direction, "S") == 0)
    {
        side_point.x = c3d->player.tile_x * TILE_SIZE;
        side_point.y = (c3d->player.tile_y + 1) * TILE_SIZE;
    }
    return (side_point);
}

/*
distance_for_dx: is the hypotenus calculated for a particular dx.
dx:              is the distance from prlayer.x to the chosen TILE'side.
if you want to print this distance, then insert the following code:
// int x1 = c3d->player.x + fabs(distance_for_dx) * cos(c3d->player.alpha_direction);
// int y1 = c3d->player.y + fabs(distance_for_dx) * sin(c3d->player.alpha_direction);
// bresenham(c3d, c3d->player.x, c3d->player.y , x1, y1, RED);
*/
double    distance_for_dx(t_c3d *c3d, int dx,  int dy, double alpha)
{
    double distance_for_dx;

    if (alpha == (M_PI / 2) || alpha == (3 * M_PI / 2))
        distance_for_dx = dy / sin(alpha);
    else
        distance_for_dx = dx / cos(alpha);
    if (fabs(distance_for_dx) > (c3d->map_fm_file.w * TILE_SIZE))
        distance_for_dx = c3d->map_fm_file.w * TILE_SIZE; //qui ho ridotto molto perchè erano lunghezze enormi man mano che ci si avvicinava a pi/2 ma vedi ora come gestire
    printf("ipotenusa tramite tg: %f\n", distance_for_dx);
    return (distance_for_dx);
}

/*
distance_for_dy: is the hypotenus calculated for a particular dy.
dy:              is the distance from prlayer.y to the chosen TILE'side.
if you want to print this distance, then insert the following code:
// int x2 = c3d->player.x + fabs(distance_for_dy) * cos(c3d->player.alpha_direction);
// int y2 = c3d->player.y + fabs(distance_for_dy) * sin(c3d->player.alpha_direction);
// bresenham(c3d, c3d->player.x, c3d->player.y , x2, y2, WHITE);
*/
double    distance_for_dy(t_c3d *c3d, int dx,  int dy, double alpha)
{
    double distance_for_dy;

    if (alpha == (3 * M_PI / 2) || alpha == (2 * M_PI) || alpha == (0))
        distance_for_dy = dx / sin(alpha);
    else
        distance_for_dy = dy / sin(alpha);
    if (fabs(distance_for_dy) > (c3d->map_fm_file.h * TILE_SIZE))
        distance_for_dy = c3d->map_fm_file.h * TILE_SIZE; //qui ho ridotto molto perchè erano lunghezze enormi man mano che ci si avvicinava a pi/2 ma vedi ora come gestire
    printf("ipotenusa tramite tg: %f\n", distance_for_dy);
    return (distance_for_dy);
}

t_point reaching_first_side(t_c3d *c3d, t_ray *ray, double alpha)
{
    t_point first_side_point;
    int dx;
    int dy;
    double  dist_for_dx;
    double  dist_for_dy;
   

    first_side_point = chose_side_point(c3d, ray);
    dx = fabs(first_side_point.x - c3d->player.x);
    dy = fabs(c3d->player.y - first_side_point.y);

    printf("ecco finalmente le tue coordinate: %d, %d\n", c3d->player.tile_x, c3d->player.tile_y);
    printf("la prima cella verso cui il raggio si sta dirigendo è: %d, %d\n",first_side_point.x, first_side_point.y );
    printf("and these are the distance from the cell. Dx = %d, Dy = %d\n", dx, dy);
    dist_for_dx = distance_for_dx(c3d, dx, dy, alpha);
    dist_for_dy = distance_for_dy(c3d, dx, dy, alpha);

    /*
    I Verify what is the shorter distance (I use fabs to avoid negatives)
    I return the end-point of the shortest distance.
    */
    if (fabs(dist_for_dx) <= fabs(dist_for_dy))
    {
        first_side_point.x = c3d->player.x + fabs(dist_for_dx) * cos(alpha);
        first_side_point.y = c3d->player.y + fabs(dist_for_dx) * sin(alpha);
    }
    else
    {
        first_side_point.x = c3d->player.x + fabs(dist_for_dy) * cos(alpha);
        first_side_point.y = c3d->player.y + fabs(dist_for_dy) * sin(alpha);
    }
    printf("punto di impatto: %d, %d\n",first_side_point.x, first_side_point.y);
    return (first_side_point);
}