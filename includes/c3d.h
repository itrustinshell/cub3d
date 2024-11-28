#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <ctype.h> //this is for isspace
#include <math.h>
#include "mlx.h"
#include "libft.h"
#include <X11/X.h>
#include <X11/keysym.h>

#define PATH_TO_TEXTURE "res/texture/muro.xpm"

//Error messages
#define INVALID_PARAMS "The only allowed parameter is the path of the map!\nUsage:\n./cub3d <map_path>\n"

//aaa rimpiazza strcat e altre di libft
//attanziena realloc
#define INCREMENT_X 1
#define INCREMENT_Y 0

#define True 1
#define False 0

//keycode
#define KEY_W 119
#define KEY_S 115
#define KEY_A 97
#define KEY_D 100
#define ESC 65307
#define ARROW_LEFT 65361
#define ARROW_RIGHT 65363

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

//calculations
#define EPSILON 1e-9 //to better manage precision erro. 1e-6 = (0.000001): used when a small tolerance is acceptable.

//angles utils
#define M_PI 3.14159265358979323846
#define DEGREE 2 * M_PI / 150

//checks pint on the circumference when the player is at the center of a circumference
#define CIRCUMFERENCE_CHECKS 8

//map_img_charateristics
#define TILE_SIZE 64

//player charactieristics .........AAAAAAAAAAAAA
#define RAY_LENGTH RADIUS * 8
#define FOOT_STEP 1
#define RADIUS 10

//camera

#define CAMERA_DISTANCE RADIUS * 10
#define FOV_ANGLE (M_PI / 2.5)

//3d
#define SCALE_FACTOR 10000 //for projection

// 3D Resolution
#define NUM_OF_RAYS 641

typedef struct s_dimension
{
	int w;
	int h;

} t_dimension;

typedef struct s_win
{
	void	*mlx_win;
	t_dimension dimension;
} t_win;

typedef struct s_color
{
	char	c;
	int		color;
} t_color;

typedef struct s_my_texture
{
	t_dimension dimension;
	char	*data_addr;
	int how_many_colors;
	t_color	color;

} t_my_texture;

typedef struct s_map
{
	char	*data;
	t_dimension dimension;
	char	**grid;
	int		x;
	int		y;
} t_map;

typedef struct s_img
{
	void		*img;
	char		*data_addr;
	int			size_line;
	int			bits_per_pixel;
	int			endian;
	t_dimension	img_dimension;
}	t_img;

typedef struct	s_point
{
	double	x;
	double	y;
} t_point;

typedef struct s_fov
{
	double	angle;
	double	half_left;
	double	half_right;

} t_fov;

typedef struct s_projection
{
	t_point point;
	double	length;
} t_projection;

typedef struct s_viwe3d
{
	double	height_wall_line;
	double	x_wall_line;
} t_view3d;

typedef struct s_ray
{
	int				cardinal_direction;
	t_point			first_side_point; // è uno dei 4 vertici interni della cella
	t_point			first_impact_point; //è il primo punto diimpatto in quella cella
	t_point			delta;
	t_point			path;
	t_point			first_point;
	t_point			end_point;
	t_projection	projection;
	t_view3d		view3d;
	int				last_increment;
	int				orientation;
} t_ray;

typedef struct s_move
{
	int			w;
	int			a;
	int			s;
	int			d;
} t_move;

typedef struct s_player
{
	t_point		position;
	t_point		tile;
	t_move		move;
	t_fov		fov;
	int			cardinal_direction;
	double		direction;
	double		perpendicular_direction;
	double		rotate_alpha_right;
	double		rotate_alpha_left;
	t_ray		ray;
} t_player;

//for norm reasons this wrap all important info
typedef struct s_c3d
{
	void		*mlx_connection;
	t_win 		win_2d;
	t_win		win_3d;
	t_map		raw_map;
	t_img		map;
	t_img		texture;
	t_img		scene_3d;
	t_img		ceil;
	t_img		floor;
	t_player	player;
} t_c3d;

int	get_direction(double perpendicular_direction);
//texture
int		find_x_texture(t_point impact_point, t_ray ray);
void	set_texture(t_img *texture, void *mlx_connection);

//closing
int		on_destroy(t_c3d *c3d);
void	error_exit(t_c3d *c3d, char *message);

//3d
t_point	find_two_lines_intersection(t_point p1, double p1_angle, t_point p2, double p2_angle);
double	find_x_3d(double ray_angle, double fov_left_ray, double win_width);
double	pitagora_theorem(t_point first_point, t_point second_point);
double	calculate_3d_wall_height(t_player player);

//img
void	create_visualize_2d_map_img(t_c3d *c3d);
int		get_pixel(t_img *img, int x, int y);
void	put_pixel(t_img *img, int x, int y, int color);

//parsing
char	*read_the_map(char *file_path);
void	get_map_dimensions(char * file_content, int *width, int *height);
char	**get_map_from_file(char *file_content, int width, int height);
void	build_map(char *path, t_c3d *c3d);

//initializing
void	initialization(t_c3d *c3d);
void	initialize_ray(t_ray *ray);
void	initialize_win(t_win *win);
void	point_init(t_point *point_to_initialize);

//window management
void	set_connection_and_windows(t_c3d *c3d);

//dda
t_ray	dda(t_point start_point, double alpha, t_c3d *c3d);
t_point	chose_side_point(t_point first_point, int cardinal_direction);
int		get_cardinal_direction(double angle);
t_point	calculate_delta(t_point first_point, t_point second_point, int cardinal_direction);
t_point	calculate_path(t_point delta, double alpha);
t_point	trigonometric_pointCalculation(t_point player_position, double path, double alpha);

//dda checks
int		is_it_inside_map_perimeter(t_point point_to_verify, t_dimension map_dimension);
int 	is_it_passing_between_two_walls(t_ray *ray, char **map_grid, t_point point_to_verify);
int 	is_it_a_wall(t_point point_to_verify, char **map_grid);

//drawing
void	draw_2d_map(t_img *img, t_c3d *c3d);
void 	draw_player(t_c3d *c3d, t_point center, int radius, int color);
void	draw_player_in_img(t_c3d *c3d);
void	draw_player_direction(t_c3d *c3d, int x0, int y0, double alpha, int color);
void	bresenham(t_c3d *c3d, int x0, int y0, int x1, int y1, int color);
void	draw_line(t_point point, double angle, int color, t_c3d *c3d);
int		get_pixel(t_img *img, int x, int y);
void	put_pixel(t_img *img, int x, int y, int color);
void	draw_2d_fov_boundaries(t_c3d *c3d);
void	draw_floor(t_c3d *c3d);
void	draw_ceiling(t_c3d *c3d);
void	draw_3d_fov(t_c3d *c3d);
void	draw_3d_scene(t_c3d *c3d);
void	drawing_routine(t_c3d *c3d);

//moving;
int		mov_key_press(int keycode, void *param);
int		mov_key_release(int keycode, void *param);
int		update_position(void *param);
void	move_player_mains(int direction, t_move move, t_point *position);
void	move_player_oblq(int direction, t_move move, t_point *position);
int		update_alpha_rotation(void *param);
int		update_movement(void *param);
int		is_collision(double player_next_x, double player_next_y, t_c3d *c3d); 
t_point	tile_reference(t_point point);

//testing
void	draw_3d_wall_height_with_one_color(double x_3d, double line_heigth, t_c3d *c3d);
void	draw_tile(char **img_data_addr, int x, int y, int color, t_c3d *c3d);