
int wall_check(t_point end_point, t_c3d *c3d, char **map_grid, t_ray *ray)
{
	if (is_it_inside_map_perimeter(end_point, c3d)) //#NOTA 1
	{
		if (is_it_passing_between_two_walls(c3d, ray, map_grid, end_point)) 
			return 1;
		if (is_it_a_wall(map_grid, end_point, c3d))
		{
			bresenham(c3d, c3d->player.coordinates.x, c3d->player.coordinates.y, end_point.x, end_point.y, PINK);
			return 1;
		}
		return 2;
	}
	else
		return 0;
	return 0;
}