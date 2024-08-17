#include "../cub3d.h"

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
                mlx_pixel_put(c3d->win.mlx_connection, c3d->win.mlx_win, center_x + x, center_y + y, WHITE);
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

