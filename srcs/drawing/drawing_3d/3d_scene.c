#include "c3d.h"

int	get_color_in_hex(char *color)
{
	// color format is: 255,255,255
	int r;
	int g;
	int b;
	char **splitted;

	splitted = ft_split(color, ',');
	r = ft_atoi(splitted[0]);
	g = ft_atoi(splitted[1]);
	b = ft_atoi(splitted[2]);
	ft_free_matrix(splitted, -1);
	return (r << 16 | g << 8 | b);
}

/*remember that the coordinates of y go greater down*/
void draw_floor(t_c3d *c3d)
{
	int x = 0;
	int y = (c3d->win_3d.dimension.h) / 2;

	while (y < c3d->win_3d.dimension.h)
	{
		x = 0;
		while (x < c3d->win_3d.dimension.w)
		{
			put_pixel(&c3d->scene_3d, x, y, get_color_in_hex(c3d->raw_map.F_color));
			x++;
		}
		y++;
	}
}

void draw_ceiling(t_c3d *c3d)
{
	int x = 0;
	int y = 0;

	while (y < (c3d->win_3d.dimension.h) / 2)
	{
		x = 0;
		while (x < c3d->win_3d.dimension.w)
		{
			put_pixel(&c3d->scene_3d, x, y, get_color_in_hex(c3d->raw_map.C_color));
			x++;
		}
		y++;
	}
}

/*disegna la scena 3d: ovvero mette tutto nello stringone:
prima il cielo, poi la terra, e poi i muri...*/
void draw_3d_scene(t_c3d *c3d)
{
	c3d->scene_3d.img_dimension = c3d->win_3d.dimension;
	c3d->scene_3d.img = mlx_new_image(c3d->mlx_connection, c3d->win_3d.dimension.w, c3d->win_3d.dimension.h);
	c3d->scene_3d.data_addr = mlx_get_data_addr(c3d->scene_3d.img, &c3d->scene_3d.bits_per_pixel, &c3d->scene_3d.size_line, &c3d->scene_3d.endian);
	draw_floor(c3d);
	draw_ceiling(c3d);
	draw_3d_fov(c3d);
    mlx_put_image_to_window(c3d->mlx_connection, c3d->win_3d.mlx_win, c3d->scene_3d.img, 0, 0);
	// draw_3d_fov(c3d);
}
