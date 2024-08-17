#include "../cub3d.h"
#include <string.h>

void dda(t_c3d *c3d)
{
	t_ray   ray;

	ray.left_alpha = c3d->player.alpha_direction - 8 * DEGREE;
	ray.right_alpha = c3d->player.alpha_direction + 8 * DEGREE;
	printf("ecco l'anfgolo: %f\n", c3d->player.alpha_direction);
	ray.cardinal_direction = get_cardinal_direction(c3d->player.alpha_direction);
	ray.first_impact_point = reaching_first_side(c3d->map_fm_file.grid,c3d->player.alpha_direction, c3d, &ray);
	if (c3d->map_fm_file.grid[(int)ray.first_impact_point.y / TILE_SIZE][(int)ray.first_impact_point.x / TILE_SIZE] == '1')
		bresenham(c3d, c3d->player.position.x, c3d->player.position.y, ray.first_impact_point.x, ray.first_impact_point.y, PURPLE);
	else
		increment(&ray, c3d, c3d->map_fm_file.grid, c3d->player.alpha_direction);
// 	// printf("alloraaaaa: play alpha: %f\n",c3d->player.alpha_direction);
	// printf("e inveceee: play alpha: %f\n",ray.left_alpha);

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
