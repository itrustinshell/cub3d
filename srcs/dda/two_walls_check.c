#include "c3d.h"

static int check_NE_for_is_it_passing_between_two_walls(char **map_grid, double cardinal_direction, t_point point_to_verify)
{
    t_point p; //to better imporve readability
    int px; //for readability: è il p.x castato ad int
    int py; //for readability: è il p.y castato ad int

    p.x = 0; //inizializzo p
    p.y = 0; //inizializzo p
    p = point_to_verify; //associo point_to_verify a p
    px = (int)p.x; //associo a px il valore castato dell'ascissa di p 
    py = (int)p.y; //associo a py il valore castato dell'ordinata di p 
    if (cardinal_direction == NE)
    {
        if (map_grid[py / TILE_SIZE][(px - 1) / TILE_SIZE] == IS_A_WALL && map_grid[(py + 1) / TILE_SIZE][(px / TILE_SIZE)] == IS_A_WALL)
        {
            p.x = p.x - 1;
            p.y = p.y + 1;
          //bresenham(c3d, c3d->player.position.x, c3d->player.position.y, point_to_verify.x, point_to_verify.y, RED);
            return (THROUGH_TWO_WALLS);
        }
    }
    return (NOT_THROUGH_TWO_WALLS);
}

static int check_NW_for_is_it_passing_between_two_walls(char **map_grid, double cardinal_direction, t_point point_to_verify)
{
    t_point p; //to better imporve readability
    int px; //for readability: è il p.x castato ad int
    int py; //for readability: è il p.y castato ad int

    p.x = 0; //inizializzo p
    p.y = 0; //inizializzo p
    p = point_to_verify; //associo point_to_verify a p
    px = (int)p.x; //associo a px il valore castato dell'ascissa di p 
    py = (int)p.y; //associo a py il valore castato dell'ordinata di p 

    if (cardinal_direction == NW)
    {
        if (map_grid[py / TILE_SIZE][(px + 1) / TILE_SIZE] == IS_A_WALL && map_grid[(py + 1) / TILE_SIZE][px / TILE_SIZE] == IS_A_WALL)
        {
            p.x = p.x - 1;
            p.y = p.y + 1;
          //bresenham(c3d, c3d->player.position.x, c3d->player.position.y, point_to_verify.x, point_to_verify.y, YELLOW);
            return (THROUGH_TWO_WALLS);
        }
    }
    return (NOT_THROUGH_TWO_WALLS);
}

static int check_SE_for_is_it_passing_between_two_walls(char **map_grid, double cardinal_direction, t_point point_to_verify)
{
    t_point p; //to better imporve readability
    int px; //for readability: è il p.x castato ad int
    int py; //for readability: è il p.y castato ad int

    p.x = 0; //inizializzo p
    p.y = 0; //inizializzo p
    p = point_to_verify; //associo point_to_verify a p
    px = (int)p.x; //associo a px il valore castato dell'ascissa di p 
    py = (int)p.y; //associo a py il valore castato dell'ordinata di p 

    if (cardinal_direction == SE)
    {
        if (map_grid[py / TILE_SIZE][(px - 1) / TILE_SIZE] == IS_A_WALL && map_grid[(py - 1) / TILE_SIZE][(px / TILE_SIZE)] == IS_A_WALL)
        {
            p.x = p.x - 1;
            p.y = p.y + 1;
          //bresenham(c3d, c3d->player.position.x, c3d->player.position.y, point_to_verify.x, point_to_verify.y, YELLOW);
            return (THROUGH_TWO_WALLS);
        }
    }
    return (NOT_THROUGH_TWO_WALLS);
}

static int check_SW_for_is_it_passing_between_two_walls(char **map_grid, double cardinal_direction, t_point point_to_verify)
{
    t_point p; //to better imporve readability
    int px; //for readability: è il p.x castato ad int
    int py; //for readability: è il p.y castato ad int

    p.x = 0; //inizializzo p
    p.y = 0; //inizializzo p
    p = point_to_verify; //associo point_to_verify a p
    px = (int)p.x; //associo a px il valore castato dell'ascissa di p 
    py = (int)p.y; //associo a py il valore castato dell'ordinata di p 

    if (cardinal_direction == SW)
    {
        if (map_grid[py / TILE_SIZE][(px + 1) / TILE_SIZE] == IS_A_WALL && map_grid[(py - 1) / TILE_SIZE][px / TILE_SIZE] == IS_A_WALL)
        {
            p.x = p.x - 1;
            p.y = p.y + 1;
          //bresenham(c3d, c3d->player.position.x, c3d->player.position.y, point_to_verify.x, point_to_verify.y, YELLOW);
            return (THROUGH_TWO_WALLS);
        }
    }
    return (NOT_THROUGH_TWO_WALLS);
}

/*gli passo un punto per frlo verificare. Se il muro ha attraversato due muri, setta il corrispettivo end_point
da stampare  e ritprna 1 per fare il break.
vedere poi se è megliofare una eventuale verisone che mette piu precisione magari con double
sulla mappa*/
int is_it_passing_between_two_walls(t_ray *ray, char **map_grid, t_point point_to_verify)
{
    double direction;

    direction = ray->cardinal_direction;
    if (check_NE_for_is_it_passing_between_two_walls(map_grid, direction, point_to_verify))
        return (THROUGH_TWO_WALLS);
    else if(check_SE_for_is_it_passing_between_two_walls(map_grid, direction, point_to_verify))
        return (THROUGH_TWO_WALLS);
    else if (check_NW_for_is_it_passing_between_two_walls(map_grid, direction, point_to_verify))
        return (THROUGH_TWO_WALLS);
    else if(check_SW_for_is_it_passing_between_two_walls(map_grid, direction, point_to_verify))
        return (THROUGH_TWO_WALLS);
    return (NOT_THROUGH_TWO_WALLS);
}