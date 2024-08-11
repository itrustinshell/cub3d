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

t_point tile_point_to_chose_for_dda_calculation(t_c3d *c3d, char *direction)
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

*/
void    palyer_look_for_dx_and_dy(t_c3d *c3d, int dx_player_chosen_tile,  int dy_player_chosen_tile)
{
   
   
    double player_look_for_dx;
    double player_look_for_dy;

    if (c3d->player.alpha_direction == (M_PI / 2) || c3d->player.alpha_direction == (3 * M_PI / 2))
        player_look_for_dx = dy_player_chosen_tile / sin(c3d->player.alpha_direction);
    else
        player_look_for_dx = dx_player_chosen_tile / cos(c3d->player.alpha_direction);
    if (fabs(player_look_for_dx) > (c3d->map_fm_file.w * TILE_SIZE))
        player_look_for_dx = c3d->map_fm_file.w * TILE_SIZE; //qui ho ridotto molto perchè erano lunghezze enormi man mano che ci si avvicinava a pi/2 ma vedi ora come gestire
    //after having calculated the distance of the player_look, this function has done his work.
    //the following are to draw this line. I will use the same method used in drawing: 
    //i use again trigonometic to fine the final point of distance and then 
    //i pass all points to brenesam.
    int x1 = c3d->player.x + fabs(player_look_for_dx) * cos(c3d->player.alpha_direction);
    int y1 = c3d->player.y + fabs(player_look_for_dx) * sin(c3d->player.alpha_direction);
    bresenham(c3d, c3d->player.x, c3d->player.y , x1, y1, RED);

printf("ipotenusa tramite tg: %f\n", player_look_for_dx);
/*
now I keep-on with delta_y
*/
    // if (c3d->player.alpha_direction == (M_PI / 2) || c3d->player.alpha_direction == (3 * M_PI / 2))
    //     player_look_for_dx = dy_player_chosen_tile / sin(c3d->player.alpha_direction);
    //else
    player_look_for_dy = dy_player_chosen_tile / sin(c3d->player.alpha_direction);
    if (fabs(player_look_for_dy) > (c3d->map_fm_file.h * TILE_SIZE))
        player_look_for_dy = c3d->map_fm_file.h * TILE_SIZE; //qui ho ridotto molto perchè erano lunghezze enormi man mano che ci si avvicinava a pi/2 ma vedi ora come gestire
    //after having calculated the distance of the player_look, this function has done his work.
    //the following are to draw this line. I will use the same method used in drawing: 
    //i use again trigonometic to fine the final point of distance and then 
    //i pass all points to brenesam.
    int x2 = c3d->player.x + fabs(player_look_for_dy) * cos(c3d->player.alpha_direction);
    int y2 = c3d->player.y + fabs(player_look_for_dy) * sin(c3d->player.alpha_direction);
    bresenham(c3d, c3d->player.x, c3d->player.y , x2, y2, WHITE);
    printf("ipotenusa tramite tg: %f\n", player_look_for_dy);

}

void reaching_first_tile(t_c3d *c3d, char *direction)
{
    t_point first_tile_point;
    int dx_player_chosen_tile;
    int dy_player_chosen_tile;
  

    first_tile_point = tile_point_to_chose_for_dda_calculation(c3d, direction);
    dx_player_chosen_tile = fabs(first_tile_point.x - c3d->player.x);
    dy_player_chosen_tile = fabs(c3d->player.y - first_tile_point.y);

    printf("ecco finalmente le tue coordinate: %d, %d\n", c3d->player.tile_x, c3d->player.tile_y);
    printf("la prima cella verso cui il raggio si sta dirigendo è: %d, %d\n",first_tile_point.x, first_tile_point.y );
    printf("and these are the distance from the cell. Dx = %d, Dy = %d\n", dx_player_chosen_tile, dy_player_chosen_tile);

    //find ipotenusa along cos and sen
  
   // int di_with_ctgy;
    palyer_look_for_dx_and_dy(c3d, dx_player_chosen_tile, dy_player_chosen_tile);


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