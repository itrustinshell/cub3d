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
#define FOV_ANGLE 60.0 // Field of View angle in degrees
#define NUM_RAYS 100   // Number of rays to cast

//map_img_charateristics
#define TILE_SIZE 50

//calculations
#define EPSILON 1e-9 //to better manage precision erro. 1e-6 = (0.000001): used when a small tolerance is acceptable.

//wall_check
#define THROUGH_TWO_WALLS 1
#define WALL_INTERCEPTED 1
#define INSIDE_PERIMETER 2
#define OUTSIDE_PERIMETER 0
#define WALL_IS_NOT_INTERCEPTED 0


//choese_delta
#define DELTA_X 1
#define DELTA_Y 2

//chose_path
#define PATH_X 1
#define PATH_Y 2

//chose section
#define SECTION_X 1
#define SECTION_Y 2

//colors
#define RED 0xff0000
#define GREEN 0x00ff00
#define BLUE 0x0000ff
#define BLACK 0X000000
#define YELLOW 0xffff00
#define WHITE 0xffffff
#define PURPLE 0x800080
#define GRAY 0x808080
#define PINK 0xffc0cb

//cardinal directions
#define NE 1330
#define E 1500
#define SE 1630
#define S 1800
#define SW 1930
#define W 2100
#define NW 2230
#define N 2400

//keycode
#define KEY_W 13
#define KEY_S 1
#define KEY_A 0
#define KEY_D 2
#define ARROW_LEFT 123
#define ARROW_RIGHT 124

//player charactieristics
#define RAY_LENGTH round(RADIUS * 2)
#define FOOT_STEP 3
#define RADIUS 6

//checks pint on the circumference when the player is at the center of a circumference
#define CIRCUMFERENCE_CHECKS 8
#define DEGREE round(2 * M_PI / 360)

//start_draw indica da dove iniziare a stampare la mappa all'interno delle coordinate in mlx_win
typedef struct s_win
{
	void	*mlx_connection;
	void	*mlx_win;
	int		w;
	int		h;
} t_win;

typedef struct s_map
{
	char	*data_from_file;
	int		w;
	int		h;
	char	**grid;
	int		x;
	int		y;
} t_map;

typedef struct s_img
{
	void	*map_img;
	char	*data_img;
	int		size_line;
	int		bits_per_pixel;
	int		endian;

}	t_img;

typedef struct s_delta
{
	double	x;
	double	y;
} t_delta;

typedef struct s_path
{
	double	x;
	double	y;
} t_path;

typedef struct	s_point
{
	double	x;
	double	y;
} t_point;

typedef struct s_ray
{
	int 	cardinal_direction;
	t_point	first_side_point; // è uno dei 4 vertici interni della cella
	t_point first_impact_point; //è il primo punto diimpatto in quella cella
	t_delta delta;
	t_path 	path;
	t_point first_point;
	t_point	end_point;
	double 	left_alpha;
	double 	right_alpha;
} t_ray;

typedef struct s_player
{
	t_point		position;
	t_point		tile;
	int			move_down;
	int			move_up;
	int			move_left;
	int			move_right;
	double		alpha_direction;
	double		rotate_alpha_right;
	double		rotate_alpha_left;
	t_ray		ray;
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

//initializing
void	initialize_player(t_c3d *c3d);
void initialize_ray(t_ray *ray);

//dda
t_point dda(t_point start_point, double alpha, t_c3d *c3d);
t_point chose_side_point(t_point first_point, int cardinal_direction);
int	get_cardinal_direction(double angle);
t_delta calculate_delta(t_point first_point, t_point second_point, int cardinal_direction);
t_path calculate_path(t_delta delta, double alpha);
t_point trigonometric_pointCalculation(t_point player_position, double path, double alpha);

//dda checks
int		is_it_inside_map_perimeter(t_point point, t_c3d *c3d);
int 	is_it_passing_between_two_walls(t_c3d *c3d, t_ray *ray, char **map_grid, t_point point_to_verify);
int 	is_it_a_wall(t_point point_to_verify, char **map_grid);

//drawing
void	draw_tile(int x, int y, int color, t_c3d *c3d);
void	draw_tile_with_internal_margin(int x, int y, int color, t_c3d *c3d);
void	draw_map(t_c3d *c3d);
void	clear_current_drawing(void *mlx, void *mlx_win, int win_w, int win_h);
void 	draw_filled_circle(t_c3d *c3d, int center_x, int center_y, int radius);
void    draw_player(t_c3d *c3d, int center_x, int center_y, int radius);
void	ft_color(int x, int y, t_c3d *c3d, int color);
void	draw_2d_player_direction(t_c3d *c3d, int x0, int y0, double alpha, int color);
void 	bresenham(t_c3d *c3d, int x0, int y0, int x1, int y1, int color);
void 	draw_field_of_view( t_c3d *c3d);

//moving;
int		my_key_hook(int keycode, void *param);
int		my_key_release(int keycode, void *param);
int		key_press(int keycode, void *param);
int		key_release(int keycode, void *param);
int		update_position(void *param);
int		update_alpha_rotation(void *param);
int		update_player_movement(void *param);
int 	is_collision(int player_next_x, int player_next_y, t_c3d *c3d);
t_point tile_reference(t_point point);
//moving_utils
void    key_press_player_alpha_rotation(int keycode, t_c3d *c3d);
void    key_release_player_alpha_rotation(int keycode, t_c3d *c3d);
void 	key_press_player_position(int keycode, t_c3d *c3d);
void    key_release_player_position(int keycode, t_c3d *c3d);


//text
void	print_map(char **map, int width, int height);