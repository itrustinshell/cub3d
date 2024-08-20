#include "../cub3d.h"

void initialize_player(t_c3d *c3d)
{
	c3d->player.alpha_direction = 0;
	c3d->player.position.x = 0;
	c3d->player.position.y = 0;
	c3d->player.tile.x = 0;
	c3d->player.tile.y = 0;
	c3d->player.move.down = 0;
	c3d->player.move.up = 0;
	c3d->player.move.left = 0;
	c3d->player.move.right = 0;
	c3d->player.alpha_direction = 0;
	c3d->player.rotate_alpha_right = 0;
	c3d->player.rotate_alpha_left = 0;
	c3d->player.ray.cardinal_direction = 0;
	c3d->player.ray.first_impact_point.x = 0;
	c3d->player.ray.first_impact_point.y = 0;
	c3d->player.ray.first_point.x = 0;
	c3d->player.ray.first_point.y = 0;
	c3d->player.ray.end_point.x = 0;
	c3d->player.ray.end_point.y = 0;
	c3d->player.camera.fov = 0;
	c3d->player.camera.fov_left_point.x = 0;
	c3d->player.camera.fov_left_point.y = 0;
	c3d->player.camera.fov_rigth_point.x = 0;
	c3d->player.camera.fov_rigth_point.y = 0;
	c3d->player.camera.position.x= 0;	
	c3d->player.camera.position.y= 0;

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
	ray->left_alpha = 0;
	ray->right_alpha = 0;

}

void point_init(t_point *point_to_initialize)
{
	point_to_initialize->x = 0;
	point_to_initialize->y = 0;
}