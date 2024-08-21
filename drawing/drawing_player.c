#include "../cub3d.h"

void draw_filled_circle(t_c3d *c3d, t_point center, int radius, int color) 
{

    t_point point;

    point.x = 0;
    point.y = 0;
    point.y = -radius;
    while (point.y <= radius) 
    {
        point.x = -radius;
        while (point.x <= radius) 
        {
            if (pow(point.x, 2) + pow(point.y , 2) <= radius * radius) 
                mlx_pixel_put(c3d->win_2d.mlx_connection, c3d->win_2d.mlx_win, center.x + point.x, center.y + point.y, color);
               // mlx_pixel_put(c3d->win_2d.mlx_connection, c3d->win_3d.mlx_win, center.x + point.x, center.y + point.y, color); //for 3dmap

            point.x++;
        }
        point.y++;
    }
}

/*questa funzione è la stessa di circle...semplicemente la racchiude
in modo che è più semplice leggere draw_player che drwa_filled_circle*/
void    draw_player(t_c3d *c3d, t_point player_position, int radius, int color)
{
    draw_filled_circle(c3d, player_position, radius, color);
}

