/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpennisi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 17:20:01 by lpennisi          #+#    #+#             */
/*   Updated: 2024/12/07 19:58:15 by lpennisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c3d.h"

void	enstabilish_orient(t_ray *ray, int last_increment)
{
	int	ray_direction;

	ray_direction = ray->cardinal_direction;
	if (last_increment == INCREMENT_X)
	{
		if (ray_direction == NW || ray_direction == SW || ray_direction == W)
			ray->orientation = E;
		else
			ray->orientation = W;
	}
	else
	{
		if (ray_direction == NW || ray_direction == NE || ray_direction == N)
			ray->orientation = S;
		else
			ray->orientation = N;
	}
}

int n_corner(int x, int y, t_c3d *c3d)
{
	if (c3d->raw_map.grid[y][x + 1] == '0' && c3d->raw_map.grid[y + 1][x] == '0')
		return (1);
	return (0);
}

 int 	north(int x, int y, t_c3d *c3d)
 {
	if (c3d->raw_map.grid[y][x] == '1')
		return (1);
	return (0);
 }

 int west(int x, int y, t_c3d *c3d)
 {
	if (c3d->raw_map.grid[y][x] == '1')
		return (1);
	return (0);
 }


static t_point	calculate_end_point(t_ray *ray, double alpha, t_c3d *c3d)
{
	t_point end_point;
	int start;
	double remind;
	t_point n_normalized_ep;
	
	if (fabs(ray->path.x) < fabs(ray->path.y))
	{
		c3d->player.ray.last_increment = INCREMENT_X;
		end_point = trigonometric_point_calc(ray->first_point, ray->path.x, alpha);
	
		n_normalized_ep.x = end_point.x - 35;
		n_normalized_ep.y = end_point.y - 35;
		int y = (int)n_normalized_ep.y / TILE_SIZE;
		int x = (int)n_normalized_ep.x / TILE_SIZE;
	
		if (is_it_a_wall(end_point, c3d->raw_map.grid))
		{
			if (north(x, y, c3d) && !north(x, y + 1, c3d) && !n_corner(x, y, c3d) && !north(x + 1, y + 1, c3d))
			{
				start = ((int)(end_point.x / TILE_SIZE)) * TILE_SIZE;
				remind = fabs(start - end_point.x);
				if (remind == 63 || remind == 0)
				{
					c3d->player.ray.last_increment = INCREMENT_Y;
					end_point = trigonometric_point_calc(ray->first_point, ray->path.y, alpha);
				}
			}
		}
	}
	else
	{
		c3d->player.ray.last_increment = INCREMENT_Y;
		end_point = trigonometric_point_calc(ray->first_point, ray->path.y, alpha);
		n_normalized_ep.x = end_point.x - 35;
		n_normalized_ep.y = end_point.y - 35;
		int y = (int)n_normalized_ep.y / TILE_SIZE;
		int x = (int)n_normalized_ep.x / TILE_SIZE;
		
		if (is_it_a_wall(end_point, c3d->raw_map.grid))
		{
			if (west(x, y, c3d) && !west(x + 1, y, c3d) && !n_corner(x, y, c3d) && !west(x + 1, y + 1, c3d))
			{
				start = ((int)(end_point.y / TILE_SIZE)) * TILE_SIZE;
				remind = fabs(start  - end_point.y  );
				if (remind == 0 || remind == 63)
				{
					c3d->player.ray.last_increment = INCREMENT_X;
					end_point = trigonometric_point_calc(ray->first_point, ray->path.x, alpha);
				}
			}
		}
	}
	return (end_point);
}

static int	check_wall_collision(t_ray *ray, t_c3d *c3d)
{
	if (is_it_passing_between_two_walls(ray, c3d->raw_map.grid, ray->end_point))
		return (TRUE);
	if (is_it_a_wall(ray->end_point, c3d->raw_map.grid))
		return (TRUE);
	return (FALSE);
}

t_ray	dda(t_point start_point, double alpha, t_c3d *c3d)
{
	t_ray	ray;

	initialize_ray(&ray);
	ray.cardinal_direction = get_cardinal_direction(alpha);
	ray.first_point = start_point;
	while (is_it_inside_map_perimeter(ray.first_point, c3d->raw_map.dimension))
	{
		ray.first_side_point = chose_side_point(ray.first_point, \
		ray.cardinal_direction);
		ray.delta = calc_delta(ray.first_point, \
		ray.first_side_point, ray.cardinal_direction);
		ray.path = calculate_path(ray.delta, alpha);
		ray.end_point = calculate_end_point(&ray, alpha, c3d);
		if (check_wall_collision(&ray, c3d))
			break ;
		ray.first_point = ray.end_point;
	}
	enstabilish_orient(&ray, c3d->player.ray.last_increment);
	return (ray);
}
