#include "../cub3d.h"

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


/*this print the little sement that come out form the little circumference on 2d map. 
it represent where the olayer is looking at*/
void draw_2d_player_direction(t_c3d *c3d, int x0, int y0, double alpha, int color) 
{
    int x1;
    int y1;
    
    x1 = x0 + RAY_LENGTH * cos(alpha);
    y1 = y0 + RAY_LENGTH * sin(alpha);
    bresenham(c3d, x0, y0, x1, y1, color);
}


void bresenham(t_c3d *c3d, int x0, int y0, int x1, int y1, int color) 
{
    int delta_x = abs(x1 - x0);
    int delta_y = abs(y1 - y0);
    int sx, sy;

    if (x0 < x1) {
        sx = 1;
    } else {
        sx = -1;
    }

    if (y0 < y1) {
        sy = 1;
    } else {
        sy = -1;
    }

    int err = delta_x - delta_y;

    while (1) 
    {
        mlx_pixel_put(c3d->win.mlx_connection, c3d->win.mlx_win, x0, y0, color);
        if (x0 == x1 && y0 == y1) break;
        int e2 = 2 * err;
        if (e2 > -delta_y) {
            err -= delta_y;
            x0 += sx;
        }
        if (e2 < delta_x) {
            err += delta_x;
            y0 += sy;
        }
    }
}