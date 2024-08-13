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

//map_img_charateristics
#define TILE_SIZE 50

//calculations
#define EPSILON 1e-6 //to better manage precision erro. 1e-6 = (0.000001): used when a small tolerance is acceptable.

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

//keycode
#define KEY_W 13
#define KEY_S 1
#define KEY_A 0
#define KEY_D 2
#define ARROW_LEFT 123
#define ARROW_RIGHT 124

//player charactieristics
#define RAY_LENGTH round((RADIUS * 2))
#define FOOT_STEP 3
#define RADIUS 6

//checks pint on the circumference when the player is at the center of a circumference
#define CIRCUMFERENCE_CHECKS 8
#define DEGREE round(2 * round(M_PI / 360));

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


typedef struct	s_point
{
	double	x;
	double	y;
} t_point;

typedef struct s_ray
{
	double		dx;
	double 	dy;

	char 	*cardinal_direction;
	double 	sx;
	double 	sy;
	double	path_x;
	double	path_y;
	double		DxTemp;
	double		DyTemp;;
	t_point	first_side_point; // è uno dei 4 vertici interni della cella
	t_point first_impact_point; //è il primo punto diimpatto in quella cella
	t_point	end_point;
	t_point	end_point_to_check;
	double 	left_alpha;
	double 	right_alpha;
	

} t_ray;

typedef struct s_player
{
	t_point		coordinates;
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

void initialize_player(t_c3d *c3d);

//calculation
void	dda(t_c3d *c3d);
void	reaching_first_side(t_c3d *c3d, t_ray *ray, double alpha);
t_point	chose_side_point(t_c3d *c3d, t_ray *ray);
void	calculate_sx_sy(t_c3d *c3d, t_ray *ray, double alpha, char *chose_sx_or_sy);

void 	calculate_dx_dy(t_c3d *c3d, t_ray *ray, char *chose_dx_or_dy);

void	get_cardinal_direction(double angle, t_ray *ray);
int		is_it_inside_map_perimeter(t_point point, t_c3d *c3d);
t_point	increment(t_ray *ray, t_c3d *c3d, char **map_grid, double alpha);

//increment_measurement

t_point	calculation_of_end_point_to_check_along_path_x(t_c3d *c3d, t_ray *ray, double alpha);
t_point calculation_of_end_point_to_check_along_path_y(t_c3d *c3d, t_ray *ray, double alpha);
double    calculation_of_temporarySX_SY(int map_length, double deltaX, double deltaY, double alpha, char *chose_sx_or_sy);




// increment_utils
int is_it_passing_between_two_walls(t_c3d *c3d, t_ray *ray, char **map_grid, t_point point_to_verify);
//int is_it_a_wall_for_increment_x(t_c3d *c3d, t_ray *ray);
//int is_it_a_wall_for_increment_y(t_c3d *c3d, t_ray *ray);
int	is_it_inside_map_perimeter(t_point point, t_c3d *c3d);

int is_it_a_wall(char **map_grid, t_point point_to_verify, t_c3d *c3d);



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


//moving;
int my_key_hook(int keycode, void *param);
int my_key_release(int keycode, void *param);
int key_press(int keycode, void *param);
int key_release(int keycode, void *param);
int update_position(void *param);
int update_alpha_rotation(void *param);
int update_player_movement(void *param);
int is_collision(int player_next_x, int player_next_y, t_c3d *c3d);
void	update_player_tile_reference(t_c3d *c3d);
//moving_utils
void    key_press_player_alpha_rotation(int keycode, t_c3d *c3d);
void    key_release_player_alpha_rotation(int keycode, t_c3d *c3d);
void 	key_press_player_position(int keycode, t_c3d *c3d);
void    key_release_player_position(int keycode, t_c3d *c3d);


//text
void	print_map(char **map, int width, int height);