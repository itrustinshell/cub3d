#include "../cub3d.h"

void initialize_player(t_c3d *c3d)
{
	c3d->player.direction = 0;
	c3d->player.perpendicular_direction = 0;
	c3d->player.position.x = 0;
	c3d->player.position.y = 0;
	c3d->player.tile.x = 0;
	c3d->player.tile.y = 0;
	c3d->player.move.down = 0;
	c3d->player.move.up = 0;
	c3d->player.move.left = 0;
	c3d->player.move.right = 0;
	c3d->player.rotate_alpha_right = 0;
	c3d->player.rotate_alpha_left = 0;
	c3d->player.ray.cardinal_direction = 0;
	c3d->player.ray.first_impact_point.x = 0;
	c3d->player.ray.first_impact_point.y = 0;
	c3d->player.ray.first_point.x = 0;
	c3d->player.ray.first_point.y = 0;
	c3d->player.ray.end_point.x = 0;
	c3d->player.ray.end_point.y = 0;
	c3d->player.fov.angle = FOV_ANGLE;
	c3d->player.fov.half_left = 0;
	c3d->player.fov.half_right = 0;
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
}

void point_init(t_point *point_to_initialize)
{
	point_to_initialize->x = 0;
	point_to_initialize->y = 0;
}