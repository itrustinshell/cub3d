#include "../cub3d.h"
#include <string.h>

//questa funcione riceve un punto di partenza e un angolo e quindi calcola per un singolo raggio il suo percorso fino a che non incontra un muro
t_point dda(t_point start_point, double alpha, t_c3d *c3d)
{
	t_ray   ray;
 	initialize_ray(&ray);

	ray.cardinal_direction = get_cardinal_direction(alpha);
	ray.first_point = start_point; //associo il mio endpoin al primo punto di impatto. aggiornerò man mano il mio end point
	// printf("\n\n\ninizia un nuovo raggio\n");
	while (is_it_inside_map_perimeter(ray.first_point, c3d->map_fm_file.dimension))
	{
		// printf("attuale primo punto: %f, %f\n", ray.first_point.x, ray.first_point.y);
		ray.first_side_point = chose_side_point(ray.first_point, ray.cardinal_direction); //individua uno dei vertici interni della cella
		// printf("side_point per calcolo delta: %f, %f\n", ray.first_side_point.x, ray.first_side_point.y);

		ray.delta = calculate_delta(ray.first_point, ray.first_side_point, ray.cardinal_direction); //dx viene calcolato solo qui perchè poi saranno solo incrementi fissi di TILE_SIZE
		ray.path = calculate_path(ray.delta, alpha);
		if (fabs(ray.path.x) < fabs(ray.path.y))
		{
			// printf("si sono entrato in x\n");
			ray.end_point = trigonometric_pointCalculation(ray.first_point, ray.path.x, alpha);
			if(is_it_passing_between_two_walls(&ray, c3d->map_fm_file.grid,  ray.end_point))
			{
				//bresenham(c3d, start_point.x, start_point.y, ray.end_point.x, ray.end_point.y, RED);
				break;
			}
		}
		else
			ray.end_point = trigonometric_pointCalculation(ray.first_point, ray.path.y, alpha);
		if(is_it_passing_between_two_walls(&ray, c3d->map_fm_file.grid, ray.end_point))
		{
			//bresenham(c3d, start_point.x, start_point.y, ray.end_point.x, ray.end_point.y, RED);
			break;
		}
		if (is_it_a_wall(ray.end_point, c3d->map_fm_file.grid))
		{
			//bresenham(c3d, start_point.x, start_point.y, ray.end_point.x, ray.end_point.y, GREEN);
			break;
		}
		else
			ray.first_point = ray.end_point;
	}
	return (ray.end_point);  //da oscurare se attivi la parte sotto
}

/*
you want to divide FOV / Win_w becouse you will have a ray for evry pixel along the width.
Doing so you will have an impact point for evry line of x-pixel of your win
*/



void visualize_3d(t_c3d *c3d, t_point end_point, double saved_left_half_fov)
{
	c3d->player.ray.projection.point = find_two_lines_intersection(c3d->player.position, c3d->player.perpendicular_direction, end_point, c3d->player.direction);
	c3d->player.ray.view3d.x_wall_line = find_x_3d(c3d->player.fov.half_left, saved_left_half_fov, c3d->map_fm_file.dimension.width * TILE_SIZE);
	c3d->player.ray.projection.length = pitagora_theorem(end_point, c3d->player.ray.projection.point);
	c3d->player.ray.view3d.height_wall_line = wall_heigth_3d(c3d->player.ray.projection.length);
	draw_line_heigths(c3d->player.ray.view3d.x_wall_line,  c3d->player.ray.view3d.height_wall_line,  c3d);
}

void draw_field_of_view(t_c3d *c3d)
{
	double angle_variation;
	t_point end_point;
	double	saved_left_half_fov;

	angle_variation = FOV_ANGLE / c3d->win_3d.w;
	point_init(&end_point);

	end_point = dda(c3d->player.position, c3d->player.fov.half_left, c3d);
	bresenham(c3d, c3d->player.position.x, c3d->player.position.y, end_point.x, end_point.y, RED);
	end_point = dda(c3d->player.position, c3d->player.fov.half_right, c3d);
	bresenham(c3d, c3d->player.position.x, c3d->player.position.y, end_point.x, end_point.y, RED);


	saved_left_half_fov = c3d->player.fov.half_left;
	while (c3d->player.fov.half_left  < c3d->player.fov.half_right)
	{

		// double alpha;
		// alpha =  c3d->player.direction - (M_PI / 2);
		//c3d->player.perpendicular_direction = c3d->player.direction - (M_PI / 2);
		end_point = dda(c3d->player.position, c3d->player.fov.half_left, c3d);
		// c3d->player.ray.projection.point = find_two_lines_intersection(c3d->player.position, c3d->player.perpendicular_direction, end_point, c3d->player.direction);
		
  		// //draw_filled_circle(c3d, intersection, RADIUS / 2, BLUE);
		// //bresenham(c3d, intersection.x, intersection.y, end_point.x, end_point.y,YELLOW);

		// c3d->player.ray.view3d.x_wall_line = find_x_3d(c3d->player.fov.half_left, tmp_ray_left, c3d->map_fm_file.dimension.width * TILE_SIZE);
		// c3d->player.ray.projection.length = pitagora_theorem(end_point, c3d->player.ray.projection.point);
		// c3d->player.ray.view3d.height_wall_line = wall_heigth_3d(c3d->player.ray.projection.length);
		// // printf("projectiooon: %f\n", projection);
		// // printf("lineheiiiiiight: %f\n", line_heigth);
		// draw_line_heigths(c3d->player.ray.view3d.x_wall_line,  c3d->player.ray.view3d.height_wall_line,  c3d);
		
		visualize_3d(c3d, end_point, saved_left_half_fov);

		c3d->player.fov.half_left = c3d->player.fov.half_left + angle_variation;
		// i++;
	}
}

