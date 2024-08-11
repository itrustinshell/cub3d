#include "../cub3d.h"
#include <string.h>

/*this function is an easy way to find the direction
the player is looking at. 
this is useful to determin the coordinate of the CELL
where he should looking at.
for example if he look at 45° 
and he is in the cell 3,2 ...is possible that he will encounter something toword right and or up
*/
char *get_cardinal_direction(double angle, t_ray *ray)
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
    if (ray->cardinal_direction == NULL)
    {
        printf("hei look at this angle: %f\n",angle);
        printf("hei! qui è null!\n");  
    }
    return (ray->cardinal_direction);
}

void dda(t_c3d *c3d)
{
 
    // int increment_along_x_axis;
    // int increment_along_y_axis;
    t_ray   ray;

ray.left_alpha = c3d->player.alpha_direction - 8 * DEGREE;
ray.right_alpha = c3d->player.alpha_direction + 8 * DEGREE;

printf("ecco l'anfgolo: %f\n", c3d->player.alpha_direction);
    ray.cardinal_direction = get_cardinal_direction(c3d->player.alpha_direction, &ray);
printf("ecco la stringa: %s\n", ray.cardinal_direction);
    ray.first_side_point = reaching_first_side(c3d, &ray, c3d->player.alpha_direction);
bresenham(c3d, c3d->player.x, c3d->player.y, ray.first_side_point.x, ray.first_side_point.y, WHITE);

while (ray.left_alpha < ray.right_alpha)
{
printf("ecco l'anfgolo: %f\n", c3d->player.alpha_direction);
    ray.cardinal_direction = get_cardinal_direction(ray.left_alpha , &ray);
printf("ecco la stringa: %s\n", ray.cardinal_direction);
    ray.first_side_point = reaching_first_side(c3d, &ray, ray.left_alpha );
    // if (increment_along_x_axis)
    // {

    // }
    // if (increment_along_y_axis)
    // {

    // }
    bresenham(c3d, c3d->player.x, c3d->player.y, ray.first_side_point.x, ray.first_side_point.y, WHITE);
ray.left_alpha += DEGREE;
}
}

// void    draw_distance_from_wall(t_c3d *c3d)
// {

//    //  dda(c3d);
//     // bresenham(c3d, c3d->player.x, c3d->player.y, impact_point.x, impact_point.y, RED);
// }

/*
il ritorno di dda
lo passo a bresenam per fargli disegnare la linea
void draw_line(void *mlx, void *win, int x0, int y0, double alpha, int color) 

*/