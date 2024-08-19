#include "cub3d.h"

#define MAP_PATH 1
#define WIDTH 2
#define HEIGHT 3
#define FACTOR 80

int main(int argc, char **argv)
{
	t_c3d	c3d;
	char	*path;
	
    

	if (argc < 2)
	{
		printf("Please provide a path to a map!\nUsage:\n./cube <map_path>\n");
		exit(EXIT_FAILURE);
	}
	initialize_player(&c3d);
	path = argv[MAP_PATH];
	// c3d.win.w = atoi(argv[WIDTH]);	//TODO: Substitute with ft_atoi from libft
	// c3d.win.h = atoi(argv[HEIGHT]);	//TODO: Substitute with ft_atoi from libft
	
	c3d.win.w = 16 * FACTOR;	//TODO: Substitute with ft_atoi from libft
	c3d.win.h = 9 * FACTOR;

	c3d.map_fm_file.data_from_file = read_the_map(path);
	get_map_dimensions(c3d.map_fm_file.data_from_file, &c3d.map_fm_file.dimension.width, &c3d.map_fm_file.dimension.heigth);
	c3d.map_fm_file.grid = get_map_from_file(c3d.map_fm_file.data_from_file, c3d.map_fm_file.dimension.width, c3d.map_fm_file.dimension.heigth);
    c3d.win.mlx_connection = mlx_init();

    c3d.win.mlx_win = mlx_new_window(c3d.win.mlx_connection, c3d.win.w, c3d.win.h, "cub3d");
	
	c3d.img.map_img = mlx_new_image(c3d.win.mlx_connection, c3d.map_fm_file.dimension.width * TILE_SIZE, c3d.map_fm_file.dimension.heigth * TILE_SIZE);
	c3d.img.data_img = mlx_get_data_addr(c3d.img.map_img, &c3d.img.bits_per_pixel, &c3d.img.size_line, &c3d.img.endian);
	draw_map(&c3d);
	mlx_put_image_to_window(c3d.win.mlx_connection, c3d.win.mlx_win, c3d.img.map_img, 0, 0);

	c3d.player.position.x = 90;
	c3d.player.position.y = 90;
	c3d.player.tile = tile_reference(c3d.player.position);
	
	c3d.player.alpha_direction = 2 * M_PI;
	draw_player(&c3d, c3d.player.position, RADIUS, RED);
	camera_plane(c3d.player.position,  c3d.player.alpha_direction,  &c3d);

	//TODO: quando avrai finito tute le propeitò nlla struct della camera e le avrai determinate 
	// fai una funzione draw camera che si occupa di disegnare tutti insimee qui.
    


	
	//dda(c3d.player.position, c3d.player.alpha_direction, &c3d);
	draw_field_of_view(&c3d);

 	draw_2d_player_direction(&c3d, c3d.player.position.x, c3d.player.position.y, c3d.player.alpha_direction, BLACK);




	mlx_hook(c3d.win.mlx_win, 2, 1L << 0, key_press, &c3d); // 2 è il codice evento per KeyPress
    mlx_hook(c3d.win.mlx_win, 3, 1L << 1, key_release, &c3d); // 3 è il codic
	mlx_loop_hook(c3d.win.mlx_connection, update_player_movement, &c3d);
	mlx_loop(c3d.win.mlx_connection);
    return (0);
}
