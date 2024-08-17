#include "../cub3d.h"
#include <string.h>

t_point dda(t_point start_point, double alpha, t_c3d *c3d)
{
	t_ray   ray;


	ray.cardinal_direction = get_cardinal_direction(alpha);
	ray.first_point = start_point; //associo il mio endpoin al primo punto di impatto. aggiornerò man mano il mio end point
	printf("\n\n\ninizia un nuovo raggio\n");
	while (is_it_inside_map_perimeter(ray.first_point, c3d))
	{
		ray.first_side_point = chose_side_point(ray.first_point, ray.cardinal_direction); //individua uno dei vertici interni della cella
		ray.delta = calculate_delta(ray.first_point, ray.first_side_point, ray.cardinal_direction); //dx viene calcolato solo qui perchè poi saranno solo incrementi fissi di TILE_SIZE
		ray.path = calculate_path(ray.delta, alpha);
		if (fabs(ray.path.x) < fabs(ray.path.y))
		{
			printf("si sono entrato in x\n");
			ray.end_point = trigonometric_pointCalculation(ray.first_point, ray.path.x, alpha);
			if(is_it_passing_between_two_walls(c3d, &ray, c3d->map_fm_file.grid,  ray.end_point))
			{
			bresenham(c3d, start_point.x, start_point.y, ray.end_point.x, ray.end_point.y, BLACK);
			break;
			}
		}
		else
			ray.end_point = trigonometric_pointCalculation(ray.first_point, ray.path.y, alpha);
			if(is_it_passing_between_two_walls(c3d, &ray, c3d->map_fm_file.grid, ray.end_point))
			{
			bresenham(c3d, start_point.x, start_point.y, ray.end_point.x, ray.end_point.y, BLACK);
			break;
			}
		if (is_it_a_wall(ray.end_point, c3d->map_fm_file.grid))
		{
			bresenham(c3d, start_point.x, start_point.y, ray.end_point.x, ray.end_point.y, BLACK);
			break;
		}
		else
			ray.first_point = ray.end_point;
	}
	return (ray.end_point);  //da oscurare se attivi la parte sotto

}

void draw_field_of_view( t_c3d *c3d)
{
	double alpha_min = 0;
	double alpha_max = 0;
	
	double degree;
	degree = 0;
	degree = (2 * M_PI) / 360;
	alpha_min = c3d->player.alpha_direction - (8 * degree) ;
	alpha_max= c3d->player.alpha_direction + (8 * degree);

	while (alpha_min < alpha_max)
	{
		dda(c3d->player.position, alpha_min, c3d);
		alpha_min = alpha_min + degree;
	}
}
