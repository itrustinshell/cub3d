#include "../cub3d.h"
#include <string.h>

t_point dda(t_point start_point, double alpha, t_c3d *c3d)
{
	t_ray   ray;
 	initialize_ray(&ray);

	ray.cardinal_direction = get_cardinal_direction(alpha);
	ray.first_point = start_point; //associo il mio endpoin al primo punto di impatto. aggiornerò man mano il mio end point
	while (is_it_inside_map_perimeter(ray.first_point, c3d))
	{
		ray.first_side_point = chose_side_point(ray.first_point, ray.cardinal_direction); //individua uno dei vertici interni della cella

		ray.delta = calculate_delta(ray.first_point, ray.first_side_point, ray.cardinal_direction); //dx viene calcolato solo qui perchè poi saranno solo incrementi fissi di TILE_SIZE
		ray.path = calculate_path(ray.delta, alpha);
		if (fabs(ray.path.x) < fabs(ray.path.y))
		{
			ray.end_point = trigonometric_pointCalculation(ray.first_point, ray.path.x, alpha);
			if(is_it_passing_between_two_walls(c3d, &ray, c3d->map_fm_file.grid,  ray.end_point))
				break;
		}
		else
			ray.end_point = trigonometric_pointCalculation(ray.first_point, ray.path.y, alpha);
		if(is_it_passing_between_two_walls(c3d, &ray, c3d->map_fm_file.grid, ray.end_point))
			break;
		if (is_it_a_wall(ray.end_point, c3d->map_fm_file.grid))
			break;
		else
			ray.first_point = ray.end_point;
	}
	return (ray.end_point);  //da oscurare se attivi la parte sotto
}

void draw_field_of_view( t_c3d *c3d)
{
	double alpha_min = 0;
	double alpha_max = 0;
	t_point end_point;
	double degree;

	end_point.x = 0;
	end_point.y = 0;
	degree = 0;
	degree = 2 * M_PI / 360;
	alpha_min = c3d->player.alpha_direction - (1 * degree) ;
	alpha_max= c3d->player.alpha_direction + (20 * degree);
	// int i = 0;
	while (alpha_min < alpha_max)
	{
		end_point = dda(c3d->player.position, alpha_min, c3d);
		bresenham(c3d, c3d->player.position.x, c3d->player.position.y, end_point.x, end_point.y, YELLOW);
		// dda(c3d->player.position, alpha_min, c3d);
		alpha_min = alpha_min + degree;
		// i++;
	}
}
