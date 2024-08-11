#include "cub3d.h"

void draw_tile(int x, int y, int color, t_c3d *c3d)
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
          	ft_color(x, y, c3d, color);
            x++;
        }
        y++;
    }
}

/*this function colors with balck the last line of pixxel of 
evry cell...so the bottom and the rigth margins*/
void draw_tile_with_internal_margin(int x, int y, int color, t_c3d *c3d)
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
                ft_color(x, y, c3d, BLACK);
            else if (x == x_value + TILE_SIZE - 1)
                ft_color(x, y, c3d, BLACK);
            else 
                ft_color(x, y, c3d, color);
            x++;
        }
        y++;
    }
}

void	draw_map(t_c3d *c3d)
{
    int starting_drawing_x;
    int starting_drawing_y;
    int x;
    int y;

    starting_drawing_x = 0;
    starting_drawing_y = 0;
    y = starting_drawing_y;
    while (y < starting_drawing_y + c3d->map_fm_file.h)
    {
        x = starting_drawing_x; 
        while (x < starting_drawing_x + c3d->map_fm_file.w)
        {
           if(c3d->map_fm_file.grid[y][x] == '1')
                draw_tile_with_internal_margin(x * TILE_SIZE, y * TILE_SIZE, BLUE, c3d);              
            else if (c3d->map_fm_file.grid[y][x] == '0') 
                draw_tile_with_internal_margin(x * TILE_SIZE, y * TILE_SIZE, GREEN, c3d);            
            else 
                draw_tile_with_internal_margin(x * TILE_SIZE, y * TILE_SIZE, RED, c3d);
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





void	ft_color(int x, int y, t_c3d *c3d, int color)
{
	int	i;
	int	bytes_per_pixel;

	bytes_per_pixel = c3d->img.bits_per_pixel / 8;
	//questo i va ai bits da colorare
    //tutti insieme prendonon un unico minuscolissimo pixel e lo colorano.
    //per intenderci quel minuscolissimo pixel è composto da 32 bits.
	i = (y * c3d->img.size_line) + (x * bytes_per_pixel);
    c3d->img.data_img[i] = color & 0xFF;
    c3d->img.data_img[i + 1] = (color >> 8) & 0xFF;
    c3d->img.data_img[i + 2] = ((color >> 16) & 0xFF);
    c3d->img.data_img[i + 3] = ((color >> 24) & 0xFF);
}

//Bresenam

void draw_line(void *mlx, void *win, int x0, int y0, double alpha, int color) 
{
    int dx, dy, sx, sy, err, e2;

    int x1,  y1;
    
    x1  = x0 + RAY_LENGTH * cos(alpha);
    y1 = y0 + RAY_LENGTH * sin(alpha);

    dx = abs(x1 - x0);
    dy = abs(y1 - y0);

    // Determine the step direction for x
    sx = 0;
    if (x0 < x1) {
        sx = 1;
    } else {
        sx = -1;
    }

    // Determine the step direction for y
    sy = 0;
    if (y0 < y1) {
        sy = 1;
    } else {
        sy = -1;
    }

    err = dx - dy;

    while (1) {
        mlx_pixel_put(mlx, win, x0, y0, color);
        if (x0 == x1 && y0 == y1) break;

        e2 = 2 * err;
        if (e2 > -dy) {
            err = err - dy;
            x0 = x0 + sx;
        }
        if (e2 < dx) {
            err = err + dx;
            y0 = y0 + sy;
        }
    }
}



