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

void reaching_first_tile(t_c3d *c3d, char *direction)
{
    int first_tile_x;
    int first_tile_y;
    int dx;
    int dy;

     first_tile_x = 0;
     first_tile_y = 0;

    if (strcmp(direction, "NE") == 0)
    {
        first_tile_x = (c3d->player.tile_x + 1) * TILE_SIZE;
        first_tile_y = (c3d->player.tile_y) * TILE_SIZE;
    }
    dx = first_tile_x - c3d->player.x;
    dy = c3d->player.y - first_tile_y;

    printf("ecco finalmente le tue coordinate: %d, %d\n", c3d->player.tile_x, c3d->player.tile_y);
    printf("la prima cella verso cui il raggio si sta dirigendo è: %d, %d\n",first_tile_x, first_tile_y );
    printf("and these are the distance from the cell. Dx = %d, Dy = %d\n", dx, dy);
    //sapendo in che cella si trova 
    //sapendo la direzione dell'angolo

}

t_point dda(t_c3d *c3d)
{
    t_point impact_point;
    impact_point.x = 1;
    impact_point.y = 1;
    int x0, y0, x1, y1;
    char *direction;
   // int dx, dy = TILE_SIZE;

    x0 = c3d->player.x;
    y0 = c3d->player.y;
    x1 = 0;
    y1 = 0;
    int map_x, map_y;
    map_x = 0;
    map_y = 0;
    map_x = x0 / TILE_SIZE;
    map_x = y0 / TILE_SIZE;
    printf("grid position: %d, %d\n", map_x, map_y);
    printf("ecco l'anfgolo: %f\n", c3d->player.alpha_direction);
    direction = what_direction_are_u_looking_at(c3d->player.alpha_direction);
    printf("ecco la stringa: %s\n", direction);
    reaching_first_tile(c3d, direction);
    if (strcmp(direction,"NW") == 0)
    {
        printf("yesss\n");
    }
    return (impact_point);
}

void    draw_distance_from_wall(t_c3d *c3d)
{
    t_point impact_point;
    impact_point = dda(c3d);
    bresenham(c3d, c3d->player.x, c3d->player.y, impact_point.x, impact_point.y, RED);
}

/*
il ritorno di dda
lo passo a bresenam per fargli disegnare la linea
void draw_line(void *mlx, void *win, int x0, int y0, double alpha, int color) 

*/