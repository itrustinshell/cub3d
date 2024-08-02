#include "cub3d.h"

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



void design_map(void *mlx, void *mlx_win, int x, int y, char **map, int w, int h)
{
    int x_value;
    int y_value;    

    x_value = x;
    y_value = y;
    while (y < y_value + h)
    {
        x = x_value; 
        while (x < x_value + w)
        {
           if(map[y][x] == '1')
           {
              draw_tile(mlx, mlx_win, x * TILE_SIZE, y * TILE_SIZE, BLUE);              
           } 
            else if (map[y][x] == '0') 
                draw_tile(mlx, mlx_win, x * TILE_SIZE, y * TILE_SIZE, GREEN);            
            else 
            {
                draw_tile(mlx, mlx_win, x * TILE_SIZE, y * TILE_SIZE, RED);              
            }
            x++;
        }
        y++;

    }
}


