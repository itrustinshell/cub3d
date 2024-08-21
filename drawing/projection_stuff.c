#include "../cub3d.h"

/*if you know a point and an angle, you can determin the line passing for that point
along that direction. You can use the linear equation of a line. Indeed the angula coefficient
in the equation (m) is the tan(angle).
The linear equation is: y = mx + c
where c is the impact point on y axis.
*/

void draw_line(t_point point, double angle, int color, t_c3d *c3d)
{
	double m;
	double c;

	m = tan(angle);
	c = point.y - (m * point.x);
	
	while (point.x < 10 * TILE_SIZE)
	{
		point.y = m * point.x + c;
		mlx_pixel_put(c3d->win_2d.mlx_connection, c3d->win_2d.mlx_win, point.x, point.y, color);
		point.x++;
	}
}
