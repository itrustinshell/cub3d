#include "../cub3d.h"

void initialize_player(t_c3d *c3d)
{
	c3d->player.alpha_direction = 0;
	c3d->player.move_down = 0;
	c3d->player.x = 0;
	c3d->player.y = 0;
	c3d->player.tile_x = 0;
	c3d->player.tile_y = 0;
	c3d->player.move_down = 0;
	c3d->player.move_up = 0;
	c3d->player.move_left = 0;
	c3d->player.move_right = 0;
	c3d->player.alpha_direction = 0;
	c3d->player.rotate_alpha_right = 0;
	c3d->player.rotate_alpha_left = 0;
	c3d->player.ray.cardinal_direction = NULL;
	c3d->player.ray.dx = 0;
	c3d->player.ray.dy = 0;
	c3d->player.ray.sx = 0;
	c3d->player.ray.sy = 0;
	c3d->player.ray.first_impact_point.x = 0;
	c3d->player.ray.first_impact_point.y = 0;
	c3d->player.ray.end_point.x = 0;
	c3d->player.ray.end_point.y = 0;
}
