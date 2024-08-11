

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
	c3d.map_fm_file.data_from_file = read_the_map(path);
	get_map_dimensions(c3d.map_fm_file.data_from_file, &c3d.map_fm_file.w, &c3d.map_fm_file.h);
	c3d.map_fm_file.grid = get_map_from_file(c3d.map_fm_file.data_from_file, c3d.map_fm_file.w, c3d.map_fm_file.h);
    c3d.win.mlx_connection = mlx_init();
	c3d.win.w = 500;
	c3d.win.h = 500;
    c3d.win.mlx_win = mlx_new_window(c3d.win.mlx_connection, c3d.win.w, c3d.win.h, "cub3d");
	
	c3d.img.map_img = mlx_new_image(c3d.win.mlx_connection, c3d.map_fm_file.w * TILE_SIZE, c3d.map_fm_file.h * TILE_SIZE);
	c3d.img.data_img = mlx_get_data_addr(c3d.img.map_img, &c3d.img.bits_per_pixel, &c3d.img.size_line, &c3d.img.endian);
	draw_map(&c3d);
	mlx_put_image_to_window(c3d.win.mlx_connection, c3d.win.mlx_win, c3d.img.map_img, 0, 0);

	c3d.player.x = 90;
	c3d.player.y = 90;

	draw_player(&c3d, c3d.player.x, c3d.player.y, RADIUS);
    


	c3d.player.alpha_direction = 45.0;

 	draw_line(c3d.win.mlx_connection, c3d.win.mlx_win, c3d.player.x, c3d.player.y, c3d.player.alpha_direction, BLACK);




	mlx_hook(c3d.win.mlx_win, 2, 1L << 0, key_press, &c3d); // 2 è il codice evento per KeyPress
    mlx_hook(c3d.win.mlx_win, 3, 1L << 1, key_release, &c3d); // 3 è il codic

	mlx_loop_hook(c3d.win.mlx_connection, update, &c3d);
	mlx_loop(c3d.win.mlx_connection);
    return (0);
}
