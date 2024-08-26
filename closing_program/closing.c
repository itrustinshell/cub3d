#include "../cub3d.h"

void	close_program(t_c3d *c3d)
{
	mlx_destroy_image(c3d->mlx_connection, c3d->map.img);
	mlx_destroy_image(c3d->mlx_connection, c3d->texture.img);

	c3d->map.img = NULL;
	mlx_destroy_window(c3d->mlx_connection, c3d->win_2d.mlx_win);
    mlx_destroy_window(c3d->mlx_connection, c3d->win_3d.mlx_win);

	c3d->win_2d.mlx_win = NULL;
    c3d->win_3d.mlx_win = NULL;

	exit(1);
}

//click x and close window
int	close_win(t_c3d *c3d)
{


	printf( "Programma chiuso con successo\n");
	close_program(c3d);
	return (0);
}

//press esc and close window
int	esc(int esc, t_c3d *c3d)
{


	if (esc == 53)
	{
		printf("Programma chiuso con successo\n");
		close_program(c3d);
	}
	return (0);
}
