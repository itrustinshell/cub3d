#include "../cub3d.h"
#include <string.h>


/*this function chose the side of the tile, and consequently the point 
according to angle_direction. This is useful to get the later the distance
dx and dy from that side.
*/
t_point chose_side_point(t_c3d *c3d, char *direction)
{
    t_point tile_point;

    if (strcmp(direction, "NE") == 0 || strcmp(direction, "E") == 0)
    {
        tile_point.x = (c3d->player.tile_x + 1) * TILE_SIZE;
        tile_point.y = c3d->player.tile_y * TILE_SIZE;
    }
    if (strcmp(direction, "NW") == 0 || strcmp(direction, "W") == 0 || strcmp(direction, "N") == 0)
    {
        tile_point.x = c3d->player.tile_x * TILE_SIZE;
        tile_point.y = c3d->player.tile_y * TILE_SIZE;
    }
    if (strcmp(direction, "SE") == 0)
    {
        tile_point.x = (c3d->player.tile_x + 1) * TILE_SIZE;
        tile_point.y = (c3d->player.tile_y + 1) * TILE_SIZE;
    }
    if (strcmp(direction, "SW") == 0 || strcmp(direction, "S") == 0)
    {
        tile_point.x = c3d->player.tile_x * TILE_SIZE;
        tile_point.y = (c3d->player.tile_y + 1) * TILE_SIZE;
    }
    return (tile_point);
}

/*
this functions calculates how much the hypotenus (which is the player_look)
will move along his line for a Delta X or Delta Y.
This is the basis of DDA algorithm.
You will see a difference in the lenght of the two distances (one calculated for dx and
one calculate for dy).

dx is the distance from prlayer to the chosen side of thr TILE.
*/
double    distance_for_dx(t_c3d *c3d, int dx,  int dy)
{
    double distance_for_dx;

    if (c3d->player.alpha_direction == (M_PI / 2) || c3d->player.alpha_direction == (3 * M_PI / 2))
        distance_for_dx = dy / sin(c3d->player.alpha_direction);
    else
        distance_for_dx = dx / cos(c3d->player.alpha_direction);
    if (fabs(distance_for_dx) > (c3d->map_fm_file.w * TILE_SIZE))
        distance_for_dx = c3d->map_fm_file.w * TILE_SIZE; //qui ho ridotto molto perchè erano lunghezze enormi man mano che ci si avvicinava a pi/2 ma vedi ora come gestire
    //after having calculated the distance of the player_look, this function has done his work.
    //the following are to draw this line. I will use the same method used in drawing: 
    //i use again trigonometic to fine the final point of distance and then 
    //i pass all points to brenesam.
    int x1 = c3d->player.x + fabs(distance_for_dx) * cos(c3d->player.alpha_direction);
    int y1 = c3d->player.y + fabs(distance_for_dx) * sin(c3d->player.alpha_direction);
    bresenham(c3d, c3d->player.x, c3d->player.y , x1, y1, RED);
    printf("ipotenusa tramite tg: %f\n", distance_for_dx);
    return (distance_for_dx);
}

double    distance_for_dy(t_c3d *c3d, int dx,  int dy)
{
    double distance_for_dy;

    if (c3d->player.alpha_direction == (3 * M_PI / 2) || c3d->player.alpha_direction == (2 * M_PI) || c3d->player.alpha_direction == (0))
        distance_for_dy = dx / sin(c3d->player.alpha_direction);
    else
        distance_for_dy = dy / sin(c3d->player.alpha_direction);
    if (fabs(distance_for_dy) > (c3d->map_fm_file.h * TILE_SIZE))
        distance_for_dy = c3d->map_fm_file.h * TILE_SIZE; //qui ho ridotto molto perchè erano lunghezze enormi man mano che ci si avvicinava a pi/2 ma vedi ora come gestire
    //after having calculated the distance of the player_look, this function has done his work.
    //the following are to draw this line. I will use the same method used in drawing: 
    //i use again trigonometic to fine the final point of distance and then 
    //i pass all points to brenesam.
    int x2 = c3d->player.x + fabs(distance_for_dy) * cos(c3d->player.alpha_direction);
    int y2 = c3d->player.y + fabs(distance_for_dy) * sin(c3d->player.alpha_direction);
    bresenham(c3d, c3d->player.x, c3d->player.y , x2, y2, WHITE);
    printf("ipotenusa tramite tg: %f\n", distance_for_dy);
    return (distance_for_dy);
}

t_point reaching_first_side(t_c3d *c3d, char *direction)
{
    t_point first_side_point;
    int dx;
    int dy;
    double  dist_for_dx;
    double  dist_for_dy;

    first_side_point = chose_side_point(c3d, direction);
    dx = fabs(first_side_point.x - c3d->player.x);
    dy = fabs(c3d->player.y - first_side_point.y);
    printf("ecco finalmente le tue coordinate: %d, %d\n", c3d->player.tile_x, c3d->player.tile_y);
    printf("la prima cella verso cui il raggio si sta dirigendo è: %d, %d\n",first_side_point.x, first_side_point.y );
    printf("and these are the distance from the cell. Dx = %d, Dy = %d\n", dx, dy);
    dist_for_dx = distance_for_dx(c3d, dx, dy);
    dist_for_dy = distance_for_dy(c3d, dx, dy);
    if (dist_for_dx <= dist_for_dy)
    {
        first_side_point.x = c3d->player.x + fabs(dist_for_dx) * cos(c3d->player.alpha_direction);
        first_side_point.y = c3d->player.y + fabs(dist_for_dx) * sin(c3d->player.alpha_direction);

    }
    else
    {
        first_side_point.x  = c3d->player.x + fabs(dist_for_dy) * cos(c3d->player.alpha_direction);
        first_side_point.y =  c3d->player.y + fabs(dist_for_dy) * sin(c3d->player.alpha_direction);
    } 
    return (first_side_point);
    //these are the distances to subctract...
}