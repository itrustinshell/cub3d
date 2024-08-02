#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <ctype.h> //this is for isspace
#include "minilibx/mlx.h"

//aaa rimpiazza strcat e altre di libft
//attanziena realloc

#define TILE_SIZE 20

#define RED 0xff0000
#define GREEN 0x00ff00
#define BLUE 0x0000ff

typedef struct s_map_point
{
	int	mx;
	int	my;
} t_map_point;

//parsing
char	*read_the_map(char *file_path);
void	get_map_dimensions(char * file_content, int *width, int *height);
char	**get_map_from_file(char *file_content, int width, int height);

//drawing
void draw_tile(void *mlx, void *mlx_win, int x, int y, int color);
void design_map(void *mlx, void *mlx_win, int x, int y, char **map, int w, int h);

//text
void	print_map(char **map, int width, int height);