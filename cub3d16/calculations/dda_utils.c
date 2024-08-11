#include "../cub3d.h"
#include <string.h>

/*this function is an easy way to find the direction the player is looking at. 
this is useful to determin the coordinate of the CELL where he should looking at.
for example if he look at 45°, and he is in the cell 3,2
is possible that he will encounter something toword right and or up
*/
void get_cardinal_direction(double angle, t_ray *ray)
{
    if (angle == 0 || angle == 2 * M_PI)
        ray->cardinal_direction = "E";
    else if (angle == M_PI)    
        ray->cardinal_direction = "W";
    else if (angle == M_PI / 2)    
        ray->cardinal_direction = "S";
    else if (angle > 0  && angle < M_PI / 2)
        ray->cardinal_direction = "SE";
    else if (angle >  M_PI / 2  && angle < M_PI)
        ray->cardinal_direction = "SW";
    else if (angle > M_PI && angle < ((3 * M_PI) / 2))
        ray->cardinal_direction = "NW";
    else if (angle > ((3 * M_PI) / 2)  && angle < 2 * M_PI)
        ray->cardinal_direction = "NE";
    printf("you are looking at %s\n", ray->cardinal_direction);  
}

/*this function chose the side of the tile, and consequently the point 
according to angle_direction. This is useful to get the later the distance
delta_x and delta_y from that side.
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

void reaching_first_side(t_c3d *c3d, t_ray *ray, double alpha)
{
    ray->first_impact_point = chose_side_point(c3d, ray); //individua uno dei vertici interni della cella
    calculate_delta_x(c3d, ray);
    calculate_delta_y(c3d, ray);
    printf("la prima cella verso cui il raggio si sta dirigendo è: %d, %d\n", ray->first_impact_point.x,  ray->first_impact_point.y );
    printf("ray.delta_x = %d, ray.delta_y = %d\n", ray->delta_x, ray->delta_y);
    ray->path_for_delta_x = dist_along_ray_in_movement_x(c3d, ray, alpha); //rispettiva ipotenusa di delta_x
    ray->path_for_delta_y = dist_along_ray_in_movement_y(c3d, ray, alpha); //rispettiva ipotenusa di delta_y

    /*
    I Verify what is the shorter distance (I use fabs to avoid negatives)
    I return the end-point of the shortest distance.
    */
    if (fabs(ray->path_for_delta_x) <= fabs(ray->path_for_delta_y)) //confronto tra ipotenuse
    {
        ray->first_impact_point.x = c3d->player.x + fabs(ray->path_for_delta_x) * cos(alpha); //calcolo punto impatto con ipotenusa relativa a delta_x
        ray->first_impact_point.y = c3d->player.y + fabs(ray->path_for_delta_x) * sin(alpha);
    }
    else
    {
        ray->first_impact_point.x = c3d->player.x + fabs(ray->path_for_delta_y) * cos(alpha); //calcolo punto impatto con ipotenusa relativa a delta_y
        ray->first_impact_point.y = c3d->player.y + fabs(ray->path_for_delta_y) * sin(alpha);
    }
    printf("punto di impatto: %d, %d\n",ray->first_impact_point.x, ray->first_impact_point.y);
}