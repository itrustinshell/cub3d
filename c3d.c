#include "c3d.h"

#define MAP_PATH 1
#define WIDTH 2
#define HEIGHT 3
#define FACTOR 50

#include <mlx.h>
#include <stdlib.h>

t_point tile_reference(t_point point)
{
    t_point tile_reference;

    tile_reference.x = 0;
    tile_reference.y = 0;
    tile_reference.x = (int)(point.x / TILE_SIZE);
    tile_reference.y = (int)(point.y / TILE_SIZE);
    return (tile_reference);
}


//attenzione dovendo passare un puntatore di puntatori in questa funzione,
//qualora accedessi al data address tramit il parametro passato t_c3d *crd
//devi scrivvere cosi: draw_map(&(c3d)->map.data_addr, c3d); Solo questo uso 
//delle parentesi funziona. draw_map(&(c3d)->map.data_addr, c3d) non funziona.
void stuff_to_draw(t_c3d *c3d)
{
    mlx_destroy_image(c3d->mlx_connection, c3d->map.img);
    create_visualize_2d_map_img(c3d); 
    mlx_clear_window(c3d->mlx_connection, c3d->win_3d.mlx_win);
    draw_2d_fov_boundaries(c3d); 
    /*TODO inserire in qualche modo 
    questo drow nel charone...come fa draw_map...
    cosi da stamparlo a img*/
    draw_3d_scene(c3d);
}   

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




