#include "../cub3d.h"
#include <string.h>


int check_wall(t_point end_point, t_c3d *c3d, char **map_grid, t_ray *ray)
{
	if (is_it_inside_map_perimeter(end_point, c3d)) //#NOTA 1
	{
		if (is_it_passing_between_two_walls(c3d, ray, map_grid, end_point)) 
			return (THROUGH_TWO_WALLS);
		if (is_it_a_wall(map_grid, end_point, c3d))
		{
			bresenham(c3d, c3d->player.position.x, c3d->player.position.y, end_point.x, end_point.y, PINK);
			return (WALL_INTERCEPTED);
		}
		return (INSIDE_PERIMETER);
	}
	else
		return (OUTSIDE_PERIMETER);
	return (OUTSIDE_PERIMETER);
}


void	increment_chosenPath_unitl_you_find_a_wall(t_ray *ray, double alpha, t_c3d *c3d, t_point end_point, int chose_path)
{
	while (WALL_IS_NOT_INTERCEPTED) //quindi aumento di volta in volta lungo la y fino a quando non incontro un muro.
	{
		if (chose_path == PATH_X)
		{
			end_point = get_end_point(c3d->player.position, c3d->map_fm_file.w, alpha,  ray, SECTION_X);
		}
		else
		{
			end_point = get_end_point(c3d->player.position, c3d->map_fm_file.w, alpha,  ray, SECTION_Y);
		}
		if (is_it_a_wall(c3d->map_fm_file.grid, end_point, c3d))
		{
			bresenham(c3d, c3d->player.position.x, c3d->player.position.y, end_point.x, end_point.y, PINK);
			break;
		}
	}
	return;
}

t_point get_end_point(t_point player_position, int map_length, double alpha, t_ray *ray, int chose_section_x_or_y)
{
	t_point end_point;
	if (chose_section_x_or_y == SECTION_X)
	{
		ray->delta.x = fabs(ray->delta.x) + TILE_SIZE; 
		ray->path.x =  calculate_path(map_length, ray->delta.x, ray->delta.y, alpha, PATH_X);     //grazie al dx_temporaneo calcolato possiamo calcolarci il nuovi path_xoraneo           
		end_point = trigonometric_pointCalculation(player_position,ray->path.x, alpha); //ovvim
	}
	else
	{
		ray->delta.y = fabs(ray->delta.y) + TILE_SIZE;
		ray->path.y =  calculate_path(map_length, ray->delta.x, ray->delta.y, alpha, PATH_Y); 
		end_point = trigonometric_pointCalculation(player_position,ray->path.y, alpha);
	}
	return (end_point);
}
