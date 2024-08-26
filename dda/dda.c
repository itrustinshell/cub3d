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
	while (is_it_inside_map_perimeter(ray.first_point, c3d->raw_map.dimension))
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
			if(is_it_passing_between_two_walls(&ray, c3d->raw_map.grid,  ray.end_point))
			{
				//bresenham(c3d, start_point.x, start_point.y, ray.end_point.x, ray.end_point.y, RED);
				break;
			}
		}
		else
			ray.end_point = trigonometric_pointCalculation(ray.first_point, ray.path.y, alpha);
		if(is_it_passing_between_two_walls(&ray, c3d->raw_map.grid, ray.end_point))
		{
			//bresenham(c3d, start_point.x, start_point.y, ray.end_point.x, ray.end_point.y, RED);
			break;
		}
		if (is_it_a_wall(ray.end_point, c3d->raw_map.grid))
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



