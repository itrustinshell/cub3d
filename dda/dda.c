#include "../cub3d.h"
#include <string.h>

t_point dda(t_point start_point, double alpha, t_c3d *c3d)
{
	t_ray   ray;

	// ray.left_alpha = c3d->player.alpha_direction - 8 * DEGREE;
	// ray.right_alpha = c3d->player.alpha_direction + 8 * DEGREE;
	// printf("ecco l'anfgolo: %f\n", c3d->player.alpha_direction);

	ray.cardinal_direction = get_cardinal_direction(c3d->player.alpha_direction);
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









	// ray.left_alpha = c3d->player.alpha_direction - M_PI / 4;
	// //ray.right_alpha = c3d->player.alpha_direction - 15 * DEGREE;
	// while (ray.left_alpha < c3d->player.alpha_direction)
	// {
	// 	get_cardinal_direction(ray.left_alpha , &ray);
		
	// 	ray.first_impact_point = reaching_first_side(c3d->map_fm_file.grid,  ray.left_alpha,  c3d, &ray);
	// 	if (c3d->map_fm_file.grid[(int)ray.first_impact_point.y / TILE_SIZE][(int)ray.first_impact_point.x / TILE_SIZE] == '1')
	// 		bresenham(c3d, c3d->player.coordinates.x, c3d->player.coordinates.y, ray.first_impact_point.x, ray.first_impact_point.y, PURPLE);
	// 	else
	// 		increment(&ray, c3d,  c3d->map_fm_file.grid,  ray.left_alpha);
	// 	ray.left_alpha += 0.01;
	// 	printf("%d\n", i);
	// 	i++;
	// }
	// printf("ciaoooooooooooooooooooooo\n");
}
