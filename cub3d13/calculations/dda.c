#include "../cub3d.h"
#include <string.h>

/*this function is an easy way to find the direction
the player is looking at. 
this is useful to determin the coordinate of the CELL
where he should looking at.
for example if he look at 45° 
and he is in the cell 3,2 ...is possible that he will encounter something toword right and or up
*/
char *what_direction_are_u_looking_at(double angle)
{
    char *direction;

    direction = NULL;
    if (angle == 0 || angle == 2 * M_PI)
        direction = "W";
    else if (angle == M_PI)    
        direction = "E";
    else if (angle == 3 / 2 * M_PI)    
        direction = "E";
    else if (angle == M_PI / 2)    
        direction = "S";
    else if (angle > 0  && angle < M_PI / 2)
        direction = "SE";
    else if (angle >  M_PI / 2  && angle < M_PI)
        direction = "SW";
    else if (angle > M_PI && angle < ((3 * M_PI) / 2))
        direction = "NW";
    else if (angle > ((3 * M_PI) / 2)  && angle < 2 * M_PI)
        direction = "NE";
    printf("you are looking at %s\n", direction);  
    if (direction == NULL)
    {
        printf("hei look at this angle: %f\n",angle);
        printf("hei! qui è null!\n");  
    }
    return (direction);
}

void dda(t_c3d *c3d)
{
    t_point first_side;
 
    char *direction;

printf("ecco l'anfgolo: %f\n", c3d->player.alpha_direction);
    direction = what_direction_are_u_looking_at(c3d->player.alpha_direction);
printf("ecco la stringa: %s\n", direction);
    first_side = reaching_first_side(c3d, direction);
}

void    draw_distance_from_wall(t_c3d *c3d)
{
     dda(c3d);
    // bresenham(c3d, c3d->player.x, c3d->player.y, impact_point.x, impact_point.y, RED);
}

/*
il ritorno di dda
lo passo a bresenam per fargli disegnare la linea
void draw_line(void *mlx, void *win, int x0, int y0, double alpha, int color) 

*/