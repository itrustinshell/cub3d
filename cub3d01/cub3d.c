

#include "cub3d.h"

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

 //   mlx_pixel_put(mlx, mlx_win, 250, 250, 0x00FF00); 
//    square(mlx, mlx_win, 200, 300, 50);
  //  ft_draw_map(mlx, mlx_win, map, width, heigt);
   

design_map(mlx, mlx_win, 0, 0, map, width, heigth);
 
    
    mlx_loop(mlx);

    return 0;
}
