/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpennisi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 11:18:05 by lpennisi          #+#    #+#             */
/*   Updated: 2024/11/27 12:31:52 by lpennisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c3d.h"

void inizialize_map_fm_file(t_map *map)
{
	map->data = NULL;
	map->dimension.h = 0;
	map->dimension.w = 0;
	map->grid = NULL;
	map->x = 0;
	map->y = 0;
}

void initialize_player(t_player *player)
{
	player->direction = M_PI / 2;
	player->perpendicular_direction = player->direction  - (M_PI / 2);;
	player->position.x = 160;
	player->position.y = 90;
	player->tile = tile_reference(player->position);
	player->move.w = 0;
	player->move.a = 0;
	player->move.s = 0;
	player->move.d = 0;
	player->rotate_alpha_right = 0;
	player->rotate_alpha_left = 0;
	player->ray.cardinal_direction = 0;
	player->ray.first_impact_point.x = 0;
	player->ray.first_impact_point.y = 0;
	player->ray.first_point.x = 0;
	player->ray.first_point.y = 0;
	player->ray.end_point.x = 0;
	player->ray.end_point.y = 0;
	player->fov.angle = FOV_ANGLE;
	player->fov.half_left = player->direction - (FOV_ANGLE / 2) ;;
	player->fov.half_right = player->direction + (FOV_ANGLE / 2);;
	
}
void initialize_img(t_img *img)
{
	img->bits_per_pixel = 0;
	img->data_addr = NULL;
	img->endian = 0;
	img->img = NULL;
	img->img_dimension.w = 0;
	img->img_dimension.h = 0;
	img->size_line = 0;
}

void initialize_ray(t_ray *ray)
{
	ray->cardinal_direction = 0;
	ray->first_side_point.x = 0;
	ray->first_side_point.y = 0;
	ray->first_impact_point.x = 0;
	ray->first_impact_point.y = 0;
	ray->delta.x = 0;
	ray->delta.y = 0;
	ray->path.x = 0;
	ray->path.y = 0;
	ray->first_point.x = 0;
	ray->first_point.y = 0;
	ray->end_point.x = 0;
	ray->end_point.y = 0;
	ray->projection.length = 0;
	ray->projection.point.x = 0;
	ray->projection.point.y = 0;
	ray->view3d.height_wall_line = 0;
	ray->view3d.x_wall_line = 0;
	ray->last_increment = 0;
}

void initialization(t_c3d *c3d)
{
	initialize_img(&c3d->map);
	initialize_img(&c3d->texture);
	initialize_player(&c3d->player);
	initialize_win(&c3d->win_2d);
	initialize_win(&c3d->win_3d);
	inizialize_map_fm_file(&c3d->raw_map);
	c3d->mlx_connection = NULL;
}
