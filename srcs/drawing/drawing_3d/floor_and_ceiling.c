#include "c3d.h"

/*remember that the coordinates of y go greater down*/
void draw_floor(t_c3d *c3d)
{
	int x = 0;
	int y = (c3d->raw_map.dimension.heigth * TILE_SIZE) / 2;

	while (y < c3d->raw_map.dimension.heigth * TILE_SIZE)
	{
		x = 0;
		while (x < c3d->raw_map.dimension.width * TILE_SIZE)
		{
			put_pixel(&c3d->scene_3d, x, y, GRAY);
			x++;
		}
		y++;
	}
}

void draw_ceiling(t_c3d *c3d)
{
	int x = 0;
	int y = 0;

	while (y < (c3d->raw_map.dimension.heigth * TILE_SIZE) / 2)
	{
		x = 0;
		while (x < c3d->raw_map.dimension.width * TILE_SIZE)
		{
			put_pixel(&c3d->scene_3d, x, y, BLUE);
			x++;
		}
		y++;
	}
}
