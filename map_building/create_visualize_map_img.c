#include "../cub3d.h"

void create_visualize_map_img(t_c3d *c3d)
{
	c3d->map.img = mlx_new_image(c3d->mlx_connection, c3d->raw_map.dimension.width * TILE_SIZE, c3d->raw_map.dimension.heigth * TILE_SIZE);
	c3d->map.data_addr = mlx_get_data_addr(c3d->map.img, &c3d->map.bits_per_pixel, &c3d->map.size_line, &c3d->map.endian);
	draw_2d_map(&c3d->map, c3d); //a questo punto il charone ha disegnata lamappa....ora il charone lo passo a drow player per fargli colorare il playerone sopra
	mlx_put_image_to_window(c3d->mlx_connection, c3d->win_2d.mlx_win, c3d->map.img, 0, 0);

	draw_2d_fov_boundaries(c3d); /*TODO inserire in qualche modo questo drow nel charone...come fa draw_map...cosi da stamparlo a img
	per ora qui l'ho messo dopo put image altrimenti veniva sovrascritto dall'immagines*/

}
