#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <ctype.h> //this is for isspace
#include <math.h>
#include "minilibx/mlx.h"

//aaa rimpiazza strcat e altre di libft
//attanziena realloc

//keycode
#define KEY_W 13
#define KEY_S 1
#define KEY_A 0
#define KEY_D 2
#define ARROW_LEFT 123
#define ARROW_RIGHT 124

//movement
#define HAS_MOVED_UP 1
#define DID_NOT_MOVE_UP 0
#define HAS_MOVED_DOWN 1
#define DID_NOT_MOVE_DOWN 0
#define HAS_MOVED_LEFT 1
#define DID_NOT_MOVE_LEFT 0
#define HAS_MOVED_RIGHT 1
#define DID_NOT_MOVE_RIGHT 0
#define YES 1
#define NO 0

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

//delta, path, section
#define DELTA_X 1
#define DELTA_Y 2
#define PATH_X 1
#define PATH_Y 2
#define SECTION_X 1
#define SECTION_Y 2

//calculations
#define EPSILON 1e-9 //to better manage precision erro. 1e-6 = (0.000001): used when a small tolerance is acceptable.

//angles utils
#define DEGREE 2 * M_PI / 150

//wall_check
#define IS_A_WALL '1'
#define IT_IS_A_WALL 1
#define IT_IS_NOT_A_WALL 0
#define THROUGH_TWO_WALLS 1
#define NOT_THROUGH_TWO_WALLS 0
#define INSIDE_PERIMETER 1
#define OUTSIDE_PERIMETER 0
#define OUT_OF_PERIMETER 1 //this is only for collision function, indeed has a different value from OUTSIDE_PERIMETER
#define COLLISION_DETECTED 1
#define NO_COLLISION_DETECTED 0
//checks pint on the circumference when the player is at the center of a circumference
#define CIRCUMFERENCE_CHECKS 8

//map_img_charateristics
#define TILE_SIZE 64

//player charactieristics
#define RAY_LENGTH RADIUS * 8
#define FOOT_STEP 4
#define RADIUS 6

//camera
#define CAMERA_DISTANCE RADIUS * 10
#define FOV_ANGLE (M_PI / 2)

//3d
#define SCALE_FACTOR 10000 //for projection
//#define NUM_RAYS 100   // numero di raggi a cui applicare il raycast

//start_draw indica da dove iniziare a stampare la mappa all'interno delle coordinate in mlx_win
typedef struct s_win
{
	void	*mlx_win;
	int		w;
	int		h;
} t_win;

typedef struct s_dimension
{
	int width;
	int heigth;

} t_dimension;

typedef struct s_color
{
	char c;
	int	color;
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
	t_delta			delta;
	t_path			path;
	t_point			first_point;
	t_point			end_point;
	t_projection	projection;
	t_view3d		view3d;
} t_ray;

typedef struct s_move
{
	int			down;
	int			up;
	int			left;
	int			right;
} t_move;

typedef struct s_player
{
	t_point		position;
	t_point		tile;
	t_move		move;
	t_fov		fov;
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
	t_player	player;
} t_c3d;

typedef struct s_image
{
    void    *img;
    char    *data;
    int     width;
    int     height;
    int     bpp;
    int     size_line;
    int     endian;
}              t_image;
//texture
char	*read_texture(char *file_path);
char	**ft_split(const char *s, char c);
size_t	ft_strlen(const char *s);
int		find_x_texture(t_point impact_point);

//closing
int		close_win(t_c3d *c3d);
int		esc(int esc, t_c3d *c3d);
void	close_program(t_c3d *c3d);

//3d
t_point find_two_lines_intersection(t_point p1, double p1_angle, t_point p2, double p2_angle);
double  find_x_3d(double ray_angle, double fov_left_ray, double win_width);
double pitagora_theorem(t_point first_point, t_point second_point);
double calculate_3d_wall_height(double projection);

//img
void create_visualize_map_img(t_c3d *c3d);
int get_pixel(t_img *img, int x, int y);
void put_pixel(t_img *img, int x, int y, int color);
void scale_texture(t_img *src, t_img *dest, double scale);

//parsing
char	*read_the_map(char *file_path);
void	get_map_dimensions(char * file_content, int *width, int *height);
char	**get_map_from_file(char *file_content, int width, int height);
void 	build_map(char *path, t_c3d *c3d);

//initializing
void initialization(t_c3d *c3d);
void 	initialize_ray(t_ray *ray);
void	point_init(t_point *point_to_initialize);

//window management
void set_connection_and_windows(t_c3d *c3d);

//dda
t_point dda(t_point start_point, double alpha, t_c3d *c3d);
t_point chose_side_point(t_point first_point, int cardinal_direction);
int		get_cardinal_direction(double angle);
t_delta calculate_delta(t_point first_point, t_point second_point, int cardinal_direction);
t_path	calculate_path(t_delta delta, double alpha);
t_point trigonometric_pointCalculation(t_point player_position, double path, double alpha);

//dda checks
int		is_it_inside_map_perimeter(t_point point_to_verify, t_dimension map_dimension);
int 	is_it_passing_between_two_walls(t_ray *ray, char **map_grid, t_point point_to_verify);
int 	is_it_a_wall(t_point point_to_verify, char **map_grid);

//drawing

void	draw_2d_map(t_img *img, t_c3d *c3d);
void	clear_current_drawing(void *mlx, void *mlx_win, int win_w, int win_h);
void 	draw_filled_circle(t_c3d *c3d, t_point center, int radius, int color);
void    draw_player(t_c3d *c3d, t_point player_position, int radius, int color);
void	draw_player_direction(t_c3d *c3d, int x0, int y0, double alpha, int color);
void 	bresenham(t_c3d *c3d, int x0, int y0, int x1, int y1, int color);
void 	draw_field_of_view( t_c3d *c3d);
void 	stuff_to_draw(t_c3d *c3d);
void 	draw_line(t_point point, double angle, int color, t_c3d *c3d);
int 	get_pixel(t_img *img, int x, int y);
void 	put_pixel(t_img *img, int x, int y, int color);
void	draw_2d_fov_boundaries(t_c3d *c3d);

//moving;
int		my_key_hook(int keycode, void *param);
int		my_key_release(int keycode, void *param);
int		key_press(int keycode, void *param);
int		key_release(int keycode, void *param);
int		update_position(void *param);
int		update_alpha_rotation(void *param);
int		update_player_movement(void *param);
int is_collision(double player_next_x, double player_next_y, t_c3d *c3d); 
t_point tile_reference(t_point point);

//moving_utils
void    key_release_player_alpha_rotation(int keycode, t_c3d *c3d);
void    key_release_player_position(int keycode, t_c3d *c3d);

//text
void	print_map(char **map, int width, int height);


//da eliminare
// void 	key_press_playerPosition(int keycode, t_c3d *c3d);
// void    key_press_playerDirection(int keycode, t_c3d *c3d);
// void	initialize_player(t_player *player);
// void	initialize_img(t_img *img);
// void	initialize_win(t_win *win);
// void	inizialize_map_fm_file(t_map *map);
// void	draw_3d_wall_height_with_one_color(double x_3d, double line_heigth, t_c3d *c3d);
// t_camera camera_plane(t_point player_position, double player_direction, t_c3d *c3d);
// void draw_3d_wall_height_with_textute_colors(double x_3d, int x_texture, double line_heigth, t_c3d *c3d);
// void scaling(t_img *new, int scale);
