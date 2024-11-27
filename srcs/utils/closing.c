#include "c3d.h"

int	on_destroy(t_c3d *c3d)
{
	mlx_destroy_image(c3d->mlx_connection, c3d->map.img);
	mlx_destroy_image(c3d->mlx_connection, c3d->texture.img);

	c3d->map.img = NULL;
	mlx_destroy_window(c3d->mlx_connection, c3d->win_2d.mlx_win);
    mlx_destroy_window(c3d->mlx_connection, c3d->win_3d.mlx_win);

	c3d->win_2d.mlx_win = NULL;
    c3d->win_3d.mlx_win = NULL;

	return (exit(0), 0);
}

void	error_exit(t_c3d *c3d, char *message)
{
	printf("%s\n", message);
	on_destroy(c3d);
}
