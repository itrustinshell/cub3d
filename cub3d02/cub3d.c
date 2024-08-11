

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
    void *mlx;
    void *mlx_win;


	(void)argc;
	int width;
	int heigth;
	char	**map;
	char *path = argv[1];

	char *result;
	result = read_the_map(path);
	
	printf("%s\n", result);
	get_map_dimensions(result, &width, &heigth);
	printf("w: %d h: %d\n", width, heigth);
	map = get_map_from_file(result, width, heigth);
	//draw_map(map, width, heigth);
    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, 500, 500, "Hello world!");
 	design_map(mlx, mlx_win, 0, 0, map, width, heigth);
 
	mlx_pixel_put(mlx, mlx_win, 250, 250, RED);
	
	array(5, 5, width, heigth, mlx, mlx_win);

	array(6, 6, width, heigth, mlx, mlx_win);	   
   
	array(11, 11, width, heigth, mlx, mlx_win);
    mlx_loop(mlx);

    return 0;
}
