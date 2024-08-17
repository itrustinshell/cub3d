#include "../cub3d.h"

void draw_tile(int x, int y, int color, t_c3d *c3d)
{
	int	i;
	int	j;
	
	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
		  	ft_color(x + j, y + i, c3d, color);
			j++;
		}
		i++;
	}
}

/**
 * This functions iterates over the TILE_SIZE and paints, for each row,
 * the corresponding black borders, and the fills the inside of the row.
 */
void draw_tile_with_internal_margin(int x, int y, int color, t_c3d *c3d)
{
	int	col;
	int	i;

	i = 0;
	while(i < TILE_SIZE)
	{
		col = 1;
		ft_color(x, y + i, c3d, BLACK);
		ft_color(x + TILE_SIZE, y + i, c3d, BLACK);
		ft_color(x + i, y, c3d, BLACK);
		ft_color(x + i, y + TILE_SIZE, c3d, BLACK);
		while (col < TILE_SIZE - 1)
		{
			ft_color(x + col, y + i, c3d, color);
			col++;
		}
		i++;
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
				draw_tile_with_internal_margin(x * TILE_SIZE, y * TILE_SIZE, WHITE, c3d);			  
			else if (c3d->map_fm_file.grid[y][x] == '0') 
				draw_tile_with_internal_margin(x * TILE_SIZE, y * TILE_SIZE, BLACK, c3d);			
			else 
				draw_tile_with_internal_margin(x * TILE_SIZE, y * TILE_SIZE, BLACK, c3d);
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
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
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

	int err = dx - dy;

	while (1) 
	{
		mlx_pixel_put(c3d->win.mlx_connection, c3d->win.mlx_win, x0, y0, color);
		if (x0 == x1 && y0 == y1) break;
		int e2 = 2 * err;
		if (e2 > -dy) {
			err -= dy;
			x0 += sx;
		}
		if (e2 < dx) {
			err += dx;
			y0 += sy;
		}
	}
}
