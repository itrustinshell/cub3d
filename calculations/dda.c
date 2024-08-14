#include "../cub3d.h"
#include <string.h>

void dda(t_c3d *c3d)
{
	t_ray   ray;

	ray.left_alpha = c3d->player.alpha_direction - 8 * DEGREE;
	ray.right_alpha = c3d->player.alpha_direction + 8 * DEGREE;
	printf("ecco l'anfgolo: %f\n", c3d->player.alpha_direction);
	get_cardinal_direction(c3d->player.alpha_direction, &ray);
	ray.first_impact_point = reaching_first_side(c3d->map_fm_file.grid,c3d->player.alpha_direction, c3d, &ray);
	if (c3d->map_fm_file.grid[(int)ray.first_impact_point.y / TILE_SIZE][(int)ray.first_impact_point.x / TILE_SIZE] == '1')
		bresenham(c3d, c3d->player.coordinates.x, c3d->player.coordinates.y, ray.first_impact_point.x, ray.first_impact_point.y, PURPLE);
	else
		increment(&ray, c3d, c3d->map_fm_file.grid, c3d->player.alpha_direction);
// while (ray.left_alpha < ray.right_alpha)
// {
//     get_cardinal_direction(ray.left_alpha , &ray);
//     reaching_first_side(c3d, &ray, ray.left_alpha );
//     if (c3d->map_fm_file.grid[ray.first_impact_point.y / TILE_SIZE][ray.first_impact_point.x / TILE_SIZE] == '1')
//     {
//       bresenham(c3d, c3d->player.coordinates.x, c3d->player.coordinates.y, ray.first_impact_point.x, ray.first_impact_point.y, PURPLE);
//    // if (c3d->map_fm_file.grid[ray.first_impact_point.y / TILE_SIZE][ray.first_impact_point.x / TILE_SIZE] != '1')
//     }
//     else
//     {
//           increment(&ray, c3d, ray.left_alpha);
//     }
//     ray.left_alpha += DEGREE;
// }
}
