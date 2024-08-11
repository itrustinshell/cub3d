#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <ctype.h> //this is for isspace
#include "minilibx/mlx.h"
#include<math.h>

//aaa rimpiazza strcat e altre di libft
//attanziena realloc

#define TILE_SIZE 50

#define RED 0xff0000
#define GREEN 0x00ff00
#define BLUE 0x0000ff
#define BLACK 0X000000
#define YELLOW 0xffff00

// KEY
#define KEY_W 13
#define KEY_S 1
#define KEY_A 0
#define KEY_D 2
#define FOOT_STEP 1
#define ARROW_LEFT 123
#define ARROW_RIGHT 124
//

#define RAY_LENGTH (RADIUS * 2)

#define RADIUS 5
//start_draw indica da dove iniziare a stampare la mappa all'interno delle coordinate i mlx_win

typedef struct s_win
{
	void	*mlx_connection;
	void	*mlx_win;
//	void 	*img;
//	char	*data;

	int		w;
	int		h;
}
 t_win;

typedef struct s_map
{
	char	*data_from_file;
	char	**grid;
	int		w;
	int		h;
	int		start_draw_x;
	int		start_draw_y;
} t_map;

typedef struct s_img
{
	void	*map_img;
	char	*data_img;
	int		size_line;
	int		bits_per_pixel;
	int		endian;

}	t_img;

typedef struct s_player
{
	double		x;
	double		y;
	int			move_down;
	int			move_up;
	int			move_left;
	int			move_right;
	double		alpha_direction;
	double		alpha_direction_right;
	double		alpha_direction_left;
} t_player;




//for norm reasons this wrap all important info
typedef struct s_c3d
{
	t_win 		win;
	t_map		map_fm_file;
	t_img		img;
	t_player	player;
} t_c3d;

//parsing
char	*read_the_map(char *file_path);
void	get_map_dimensions(char * file_content, int *width, int *height);
char	**get_map_from_file(char *file_content, int width, int height);

//drawing
void	draw_tile(int x, int y, int color, t_c3d *c3d);
void	draw_tile_with_internal_margin(int x, int y, int color, t_c3d *c3d);
void	draw_map(t_c3d *c3d);
void	clear_current_drawing(void *mlx, void *mlx_win, int win_w, int win_h);
void 	draw_filled_circle(t_c3d *c3d, int center_x, int center_y, int radius);
void    draw_player(t_c3d *c3d, int center_x, int center_y, int radius);
void	ft_color(int x, int y, t_c3d *c3d, int color);
void	draw_line(void *mlx, void *win, int x0, int y0, double alpha, int color);



//moving;
int my_key_hook(int keycode, void *param);
int my_key_release(int keycode, void *param);
int key_press(int keycode, void *param);
int key_release(int keycode, void *param);
int update_position(void *param);
int update_alpha_direction(void *param);
int update(void *param);

//text
void	print_map(char **map, int width, int height);