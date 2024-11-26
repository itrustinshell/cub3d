#include "c3d.h"

static void set_win_dimensions(t_win *win_2d, t_win *win_3d, t_dimension map_fm_file_dimension)
{
win_2d->w = TILE_SIZE * map_fm_file_dimension.width;	//TODO: Substitute with ft_atoi from libft
win_2d->h = TILE_SIZE * map_fm_file_dimension.heigth;
win_3d->w = TILE_SIZE * map_fm_file_dimension.width;
win_3d->h = TILE_SIZE * map_fm_file_dimension.heigth;;
}

void set_connection_and_windows(t_c3d *c3d)
{
	set_win_dimensions(&c3d->win_2d, &c3d->win_3d, c3d->raw_map.dimension);
    c3d->mlx_connection = mlx_init();
    c3d->win_2d.mlx_win = mlx_new_window(c3d->mlx_connection, c3d->win_2d.w, c3d->win_2d.h, "cub3d_2d");
	c3d->win_3d.mlx_win = mlx_new_window(c3d->mlx_connection, c3d->win_3d.w, c3d->win_3d.h, "cub3d_3d");
}