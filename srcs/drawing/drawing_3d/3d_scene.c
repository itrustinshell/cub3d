#include "c3d.h"

/*remember that the coordinates of y go greater down*/
void draw_floor(t_c3d *c3d)
{
	int x = 0;
	int y = (c3d->raw_map.dimension.h * TILE_SIZE) / 2;

	while (y < c3d->raw_map.dimension.h * TILE_SIZE)
	{
		x = 0;
		while (x < c3d->raw_map.dimension.w * TILE_SIZE)
		{
			put_pixel(&c3d->scene_3d, x, y, GRAY);
			x++;
		}
		y++;
	}
}

void draw_ceiling(t_c3d *c3d)
{
	int x = 0;
	int y = 0;

	while (y < (c3d->raw_map.dimension.h * TILE_SIZE) / 2)
	{
		x = 0;
		while (x < c3d->raw_map.dimension.w * TILE_SIZE)
		{
			put_pixel(&c3d->scene_3d, x, y, BLUE);
			x++;
		}
		y++;
	}
}

/*disegna la scena 3d: ovvero mette tutto nello stringone:
prima il cielo, poi la terra, e poi i muri...*/
void draw_3d_scene(t_c3d *c3d)
{
	c3d->scene_3d.img_dimension.w = c3d->raw_map.dimension.w * TILE_SIZE;
	c3d->scene_3d.img_dimension.h = c3d->raw_map.dimension.h * TILE_SIZE;
	c3d->scene_3d.img = mlx_new_image(c3d->mlx_connection,c3d->scene_3d.img_dimension.w, c3d->scene_3d.img_dimension.h);
	c3d->scene_3d.data_addr = mlx_get_data_addr(c3d->scene_3d.img, &c3d->scene_3d.bits_per_pixel, &c3d->scene_3d.size_line, &c3d->scene_3d.endian);
	draw_ceiling(c3d);
	draw_floor(c3d);
	draw_3d_fov(c3d);
    mlx_put_image_to_window(c3d->mlx_connection, c3d->win_3d.mlx_win, c3d->scene_3d.img, 0, 0);
	// draw_3d_fov(c3d);
}
