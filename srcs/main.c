#include "c3d.h"

#define MAP_PATH 1
#define WIDTH 2
#define HEIGHT 3
#define FACTOR 50

#include <stdlib.h>

int	on_destroy(t_c3d *c3d)
{
	return (exit(0), 0);
}

void	error_exit(t_c3d *c3d, char *message)
{
	printf("%s\n", message);
	on_destroy(c3d);
}

void	parse_parameters(int argc, char **argv)
{
	if (argc != 2)
		error_exit(NULL, INVALID_PARAMS);
}

void	set_hook_and_loop(t_c3d *c3d)
{
	/*mlx_hook ha come secondo parametro il codice evento.
	il codice evento è un numero. Questo numero indica che tipologia di evento mlx:hook deve ascolatre.
	Ad esempio il numero 2 indica che ora mlx_hook è in ascolto su eventi di pressione della tastiera
	Inece ad esempio il codice 3 indica che mlx_hook è in ascolto su eventi di rilascio dei tasti della tastiera*/
	//hook for 3d scene
	mlx_hook(c3d->win_3d.mlx_win, KeyPress, KeyPressMask, &mov_key_press, c3d);
    mlx_hook(c3d->win_3d.mlx_win, KeyRelease, KeyReleaseMask, &mov_key_release, c3d);
	mlx_hook(c3d->win_3d.mlx_win, DestroyNotify, StructureNotifyMask, &on_destroy, c3d);
	//hook for 2d scene
	mlx_hook(c3d->win_2d.mlx_win, KeyPress, KeyPressMask, &mov_key_press, c3d);
    mlx_hook(c3d->win_2d.mlx_win, KeyRelease, KeyReleaseMask, &mov_key_release, c3d);
	mlx_hook(c3d->win_2d.mlx_win, DestroyNotify, StructureNotifyMask, &on_destroy, c3d);
	/*questo mlx_loop_hook ascolta costantemente per update movement
	l'update movement avviene effettivamente se ci sono
	nuovi valori ..altrimenti gli stessi valori sono richiamati
	e appunto nulla cambia....i nuovi valori sono inseriti quando
	avviene un press (gestito dalle funzioni hook di sopra).
	nel */
	mlx_loop_hook(c3d->mlx_connection, update_movement, c3d);
	mlx_loop(c3d->mlx_connection);
}

int main(int argc, char **argv)
{
	t_c3d	c3d;

	parse_parameters(argc, argv);
	initialization(&c3d);
	build_map(argv[MAP_PATH], &c3d);
	set_connection_and_windows(&c3d);
	
	create_visualize_2d_map_img(&c3d); 
	set_texture(&c3d.texture, c3d.mlx_connection);
	draw_3d_scene(&c3d);
	set_hook_and_loop(&c3d);
    return (0);
}




