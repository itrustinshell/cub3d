#include "../cub3d.h"

void initialize_player(t_c3d *c3d)
{
	c3d->player.alpha_direction = 0;
	c3d->player.move_down = 0;
	c3d->player.position.x = 0;
	c3d->player.position.y = 0;
	c3d->player.tile.x = 0;
	c3d->player.tile.y = 0;
	c3d->player.move_down = 0;
	c3d->player.move_up = 0;
	c3d->player.move_left = 0;
	c3d->player.move_right = 0;
	c3d->player.alpha_direction = 0;
	c3d->player.rotate_alpha_right = 0;
	c3d->player.rotate_alpha_left = 0;
	c3d->player.ray.cardinal_direction = NULL;
	c3d->player.ray.initialDy = 0;
	c3d->player.ray.initialDy = 0;
	c3d->player.ray.path_x = 0;
	c3d->player.ray.path_y = 0;
	c3d->player.ray.first_impact_point.x = 0;
	c3d->player.ray.first_impact_point.y = 0;
	c3d->player.ray.end_point.x = 0;
	c3d->player.ray.end_point.y = 0;
}
