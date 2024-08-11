#include "cub3d.h"


/*this function colors with balck the last line of pixxel of 
evry cell...so the bottom and the rigth margins*/
void draw_tile_with_internal_margin(void *mlx, void *mlx_win, int x, int y, int color)
{
    int x_value;
    int y_value;

    x_value = x;
    y_value = y;
    while (y < y_value + TILE_SIZE)
    {
        x = x_value;
        while (x < x_value + TILE_SIZE)
        {
            if (y == y_value + TILE_SIZE - 1)
                mlx_pixel_put(mlx, mlx_win, x, y, BLACK);  
            else if (x == x_value + TILE_SIZE - 1)
                 mlx_pixel_put(mlx, mlx_win, x, y, BLACK);
            else 
                mlx_pixel_put(mlx, mlx_win, x, y, color);
            x++;
        }
        y++;
    }
}


void draw_tile(void *mlx, void *mlx_win, int x, int y, int color)
{
    int x_value;
    int y_value;

    x_value = x;
    y_value = y;
    while (y < y_value + TILE_SIZE)
    {
        x = x_value;
        while (x < x_value + TILE_SIZE)
        {
           mlx_pixel_put(mlx, mlx_win, x, y, color);
            x++;
        }
        y++;
    }
}

void	design_map(void *mlx, void *mlx_win, int starting_drawing_x, int starting_drawing_y, char **map, int w, int h)
{
    int x;
    int y;
    //int x_value;
   // int y_value;

   // x = starting_drawing_x;
    y = starting_drawing_y;
   // x_value = starting_drawing_x;
    //y_value = starting_drawing_y;
    while (y < starting_drawing_y + h)
    {
        x = starting_drawing_x; 
        while (x < starting_drawing_x + w)
        {
           if(map[y][x] == '1')
              draw_tile_with_internal_margin(mlx, mlx_win, x * TILE_SIZE, y * TILE_SIZE, BLUE);              
            else if (map[y][x] == '0') 
                draw_tile_with_internal_margin(mlx, mlx_win, x * TILE_SIZE, y * TILE_SIZE, GREEN);            
            else 
                draw_tile_with_internal_margin(mlx, mlx_win, x * TILE_SIZE, y * TILE_SIZE, RED);
            x++;
        }
        y++;
    }
}

void    clear_current_drawing(void *mlx, void *mlx_win, int win_w, int win_h)
{
    int x;
    int y;

    x = 0;
    y = 0; 
    while (y < win_h)
    {
        x = 0;
        while (x < win_w)
        {
            mlx_pixel_put(mlx, mlx_win, x, y, BLACK);
            x++;
        }
    y++;        
    }
}

void draw_filled_circle(t_c3d *c3d, int center_x, int center_y, int radius) 
{
    int x;
    int y;

    y = -radius;
    while (y <= radius) 
    {
        x = -radius;
        while (x <= radius) 
        {
            if (x * x + y * y <= radius * radius) 
                mlx_pixel_put(c3d->win.mlx_connection, c3d->win.mlx_win, center_x + x, center_y + y, RED);
            x++;
        }
        y++;
    }
}

/*questa funzione è la stessa di circle...semplicemente la racchiude
in modo che è più semplice leggere draw_player che drwa_filled_circle*/
void    draw_player(t_c3d *c3d, int center_x, int center_y, int radius)
{
    draw_filled_circle(c3d, center_x, center_y, radius);
}


// void    draw_player()
// {



// }