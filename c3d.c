#include "cub3d.h"

#define MAP_PATH 1
#define WIDTH 2
#define HEIGHT 3
#define FACTOR 50

#include <mlx.h>
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
	create_visualize_map_img(&c3d); //TODO: finire l'immagine con player e rays
	draw_player(&c3d, c3d.player.position, RADIUS, RED);

	double scale;
	scale = 1;
	// c3d.texture.img = mlx_xpm_file_to_image(c3d.mlx_connection, "texture/mur.xpm", &c3d.texture.img_dimension.width, &c3d.texture.img_dimension.heigth);
	// if (!c3d.texture.img) 
	// {
	// 	printf("non carica la texture \n");
    // 	exit(EXIT_FAILURE);
	// }
	// c3d.texture.img_dimension.width = 64;
	// c3d.texture.img_dimension.heigth = 64;
	// c3d.texture.data_addr = mlx_get_data_addr(c3d.texture.img, &c3d.texture.bits_per_pixel, &c3d.texture.size_line, &c3d.texture.endian);
	// mlx_put_image_to_window(c3d.mlx_connection, c3d.win_2d.mlx_win, c3d.texture.img, 200, 200);

	//draw_texture(c3d.texture, &c3d);
	//scaling(c3d.texture.img, 2);
	// t_img new;
	// new.img_dimension.width = TILE_SIZE * scale;
	// new.img_dimension.heigth = TILE_SIZE * scale;
	// new.img = mlx_new_image(c3d.mlx_connection, new.img_dimension.width, new.img_dimension.heigth);
	// new.data_addr = mlx_get_data_addr(new.img, &new.bits_per_pixel, &new.size_line, &new.endian);
	
	
	// printf("this is the size_line of the img: %d\n",new.size_line);
	// printf("this is the bpp of the img: %d\n",new.bits_per_pixel);
	// printf("this is the width of the img: %d\n",new.img_dimension.width);
	// printf("this is the height of the img: %d\n",new.img_dimension.heigth);
	// size_t buffer_size = new.size_line * new.img_dimension.heigth;
	// printf("Calculated buffer size: %zu bytes\n", buffer_size);
	// scaling(&c3d.texture, &new,  scale);
	// mlx_put_image_to_window(c3d.mlx_connection, c3d.win_2d.mlx_win, new.img, 0, 0);



/*mlx_hook ha come secondo parametro il codice evento.
il codice evento è un numero. Questo numero indica che tipologia di evento mlx:hook deve ascolatre.
Ad esempio il numero 2 indica che ora mlx_hook è in ascolto su eventi di pressione della tastiera
Inece ad esempio il codice 3 indica che mlx_hook è in ascolto su eventi di rilascio dei tasti della tastiera*/
	mlx_hook(c3d.win_2d.mlx_win, 2, 1L << 0, key_press, &c3d); // 2 è il codice evento per KeyPress
    mlx_hook(c3d.win_2d.mlx_win, 3, 1L << 1, key_release, &c3d); // 3 è il codic

	//3D HOOK
	// mlx_hook(c3d.win_3d.mlx_win, 2, 1L << 0, key_press, &c3d); // 2 è il codice evento per KeyPress
    // mlx_hook(c3d.win_3d.mlx_win, 3, 1L << 1, key_release, &c3d); // 3 è il codic

	// mlx_hook(c3d.win_2d.mlx_win, 17, 0, close_win, &c3d);
	// mlx_hook(c3d.win_3d.mlx_win, 17, 0, close_win, &c3d);

	// mlx_key_hook(c3d.win_2d.mlx_win, esc, &c3d);
	// mlx_key_hook(c3d.win_3d.mlx_win, esc, &c3d);

//new work
	// t_img src;
	// t_img dest;
    // src.img = mlx_xpm_file_to_image(c3d.mlx_connection, "texture/mur.xpm", &src.img_dimension.width, &src.img_dimension.heigth);
    // src.data_addr = mlx_get_data_addr(src.img, &src.bits_per_pixel, &src.size_line, &src.endian);

    // dest.img_dimension.width = src.img_dimension.width * scale;
    // dest.img_dimension.heigth = src.img_dimension.heigth * scale;
    // dest.img = mlx_new_image(c3d.mlx_connection, dest.img_dimension.width, dest.img_dimension.heigth);
    // dest.data_addr = mlx_get_data_addr(dest.img, &dest.bits_per_pixel, &dest.size_line, &dest.endian);

    // scale_texture(&src, &dest, scale);

    // mlx_put_image_to_window(c3d.mlx_connection, c3d.win_2d.mlx_win, dest.img, 0, 0);

//with subst
	t_img src;
    src.img = mlx_xpm_file_to_image(c3d.mlx_connection, "texture/mur.xpm", &src.img_dimension.width, &src.img_dimension.heigth);
    src.data_addr = mlx_get_data_addr(src.img, &src.bits_per_pixel, &src.size_line, &src.endian);

    c3d.texture.img_dimension.width = src.img_dimension.width * scale;
     c3d.texture.img_dimension.heigth = src.img_dimension.heigth * scale;
     c3d.texture.img = mlx_new_image(c3d.mlx_connection,  c3d.texture.img_dimension.width,  c3d.texture.img_dimension.heigth);
     c3d.texture.data_addr = mlx_get_data_addr( c3d.texture.img, &c3d.texture.bits_per_pixel, &c3d.texture.size_line, &c3d.texture.endian);

    scale_texture(&src, &c3d.texture, scale);

    mlx_put_image_to_window(c3d.mlx_connection, c3d.win_2d.mlx_win,  c3d.texture.img, 0, 0);

int x = 0;
int y = 0;
	while (y < TILE_SIZE)
	{
		while (x < TILE_SIZE)
		{
		//	int color = get_pixel(&src, y, x);
//printf("color: %d\n", color );
			x++;
		}
		y++;
	}

	draw_field_of_view(&c3d);



	mlx_loop_hook(c3d.mlx_connection, update_player_movement, &c3d);
	mlx_loop(c3d.mlx_connection);

    return (0);
}




