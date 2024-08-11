# include "cub3d.h"





int main (int argc, char **argv)
{
	(void)argc;
	int width;
	int heigth;
	char	**map;
	char *path = argv[1];

	char *result;
	result = read_the_map(path);
	
	printf("%s\n", result);
	get_map_dimensions(result, &width, &heigth);
	printf("w: %dm h: %d\n", width, heigth);
	map = get_map_from_file(result, width, heigth);
	//draw_map(map, width, heigth);


}
