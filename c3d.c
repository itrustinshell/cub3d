#include "c3d.h"

#define MAP_PATH 1
#define WIDTH 2
#define HEIGHT 3
#define FACTOR 50

#include "minilibx-linux/mlx.h"
#include <stdlib.h>

int main(int argc, char **argv)
{
	t_c3d	c3d;

	if (argc < 2)
	{
		printf("Please provide a path to a map!\nUsage:\n./cube <map_path>\n");
		exit(EXIT_FAILURE);
	}
	initialization(&c3d);
	build_map(argv[MAP_PATH], &c3d);
	set_connection_and_windows(&c3d);
	
	create_visualize_2d_map_img(&c3d); 
	set_texture(&c3d.texture, c3d.mlx_connection);
	draw_3d_scene(&c3d);
	/*mlx_hook ha come secondo parametro il codice evento.
	il codice evento è un numero. Questo numero indica che tipologia di evento mlx:hook deve ascolatre.
	Ad esempio il numero 2 indica che ora mlx_hook è in ascolto su eventi di pressione della tastiera
	Inece ad esempio il codice 3 indica che mlx_hook è in ascolto su eventi di rilascio dei tasti della tastiera*/
	mlx_hook(c3d.win_2d.mlx_win, 2, 1L << 0, mov_key_press, &c3d); // 2 è il codice evento per KeyPress
    mlx_hook(c3d.win_2d.mlx_win, 3, 1L << 1, mov_key_release, &c3d); // 3 è il codic
 	
	/*questo mlx_loop_hook ascolta costantemente per update movement
	l'update movement avviene effettivamente se ci sono
	nuovi valori ..altrimenti gli stessi valori sono richiamati
	e appunto nulla cambia....i nuovi valori sono inseriti quando 
	avviene un press (gestito dalle funzioni hook di sopra).
	nel */
	mlx_loop_hook(c3d.mlx_connection, update_movement, &c3d);
	mlx_loop(c3d.mlx_connection);

    return (0);
}




