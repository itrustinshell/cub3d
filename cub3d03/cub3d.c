

#include "cub3d.h"


void	array(int x, int y, int map_x, int map_y, void *mlx, void *mlx_win)
{
	if (x * TILE_SIZE > TILE_SIZE && x * TILE_SIZE < (map_x * TILE_SIZE) && y * TILE_SIZE > TILE_SIZE && y * TILE_SIZE < (map_y * TILE_SIZE))
	{
		x = x * TILE_SIZE;
		y = y * TILE_SIZE;
		while (x < map_x * TILE_SIZE)
		{	
			mlx_pixel_put(mlx, mlx_win, x, y, RED);
			x++;
		}
	}
}


int main(int argc, char **argv)
{
	t_c3d c3d;
	(void)argc;

	printf("ecco %d\n", 45/10);
	char *path = argv[1];
	c3d.map.reading_from_file = read_the_map(path);
	get_map_dimensions(c3d.map.reading_from_file, &c3d.map.w, &c3d.map.h);
	c3d.map.grid = get_map_from_file(c3d.map.reading_from_file, c3d.map.w, c3d.map.h);
    c3d.win.mlx_connection = mlx_init();
	c3d.win.w = 500;
	c3d.win.h = 500;
    c3d.win.mlx_win = mlx_new_window(c3d.win.mlx_connection, c3d.win.w, c3d.win.h, "cub3d");
 	design_map(c3d.win.mlx_connection, c3d.win.mlx_win, 0, 0, c3d.map.grid, c3d.map.w, c3d.map.h);
	c3d.player.x = 50;
	c3d.player.y = 50;
//	draw_player(&c3d, c3d.player.x, c3d.player.y, 3);
	draw_filled_circle(&c3d, c3d.player.x, c3d.player.y, RADIUS);

/*
mlx_key_hook e mlx_hook per la gestione dei tasti
e mlx_loop_hook per l'aggiornamento continuo.

mlx_hook: Usa questa funzione per collegare gli eventi alla finestra. 
Il secondo parametro è il codice evento (2 per pressione del tasto, 3 per rilascio del tasto). 
Il terzo parametro è la "mask" dell'evento (1L << 0 per KeyPress, 1L << 1 per KeyRelease).
mlx_key_hook: Puoi usare mlx_key_hook per la pressione dei tasti, ma per il rilascio dei tasti devi usare mlx_hook.

Quinfilalogicaquiè che hai due hook che sono in ascolto sulla tastiera.
Quando digiti la tastiera il corrispettivo volore è settato a 1.
quando rilasci la tasitera il corrispettivo valore è settato a 0.
e poi hai un loop_hook che si preoccupa di costantemente aggiornare nuove posizioni.
questo loop verifica costantemente la variabile del giocaroe settata nelel precedenti funzino.
con press le setti a 1 con release le setti a 0.
quindi con loop eseguo un updating continuo che quando vede la varibaili impostate a 1 mi avanza delle unità che gli dico.
se vede la variabile impostata a zero si ferma.
quivalori 2 e 3 si riferiscono uno all'evento keypresso di minilibx
e l'altro all'evento keyrelease di minilbx. inifne accettano
quele maskere*/
	mlx_hook(c3d.win.mlx_win, 2, 1L << 0, key_press, &c3d); // 2 è il codice evento per KeyPress
    mlx_hook(c3d.win.mlx_win, 3, 1L << 1, key_release, &c3d); // 3 è il codic

	mlx_loop_hook(c3d.win.mlx_connection, update_position, &c3d);
	mlx_loop(c3d.win.mlx_connection);
    return (0);
}
