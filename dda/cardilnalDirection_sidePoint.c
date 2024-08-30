#include "../c3d.h"

int get_cardinal_direction(double angle)
{
    int cardinal_direction = 0;

	while (angle < 0)
	{
		angle += 2 * M_PI;
	}
    while (angle >= 2 * M_PI) 
	{
		angle -= 2 * M_PI;
	}
    if (fabs(angle - 0) < EPSILON || fabs(angle - 2 * M_PI) < EPSILON)
	{
		//printf("eh si queto angolo è proprio zero\n");
        cardinal_direction = E;
	}
    else if (fabs(angle - M_PI) < EPSILON)
        cardinal_direction = W;
    else if (fabs(angle - M_PI / 2) < EPSILON)
        cardinal_direction = S;
    else if (fabs(angle - (3 * M_PI) / 2) < EPSILON)
        cardinal_direction = N;
    else if (angle > 0 && angle < M_PI / 2)
        cardinal_direction = SE;
    else if (angle > M_PI / 2 && angle < M_PI)
        cardinal_direction = SW;
    else if (angle > M_PI && angle < (3 * M_PI) / 2)
        cardinal_direction = NW;
    else if (angle > (3 * M_PI) / 2 && angle < 2 * M_PI)
        cardinal_direction = NE;
    
	//printf("ma che caz di angolo è: %f\n", angle);
   // printf("You are looking at %d\n", cardinal_direction);
    return cardinal_direction;
}

/*this function chose the side of the tile, and consequently the point 
according to angle_direction. This is useful to get the later the distance
dx and dy from that side.
*/
t_point chose_side_point(t_point first_point, int cardinal_direction)
{
	t_point tile_ref;
	tile_ref.x = 0;
	tile_ref.y = 0;

	t_point side_point;
	side_point.x = 0;
	side_point.y = 0;

	tile_ref = tile_reference(first_point);
	if (cardinal_direction == NE || cardinal_direction == E || cardinal_direction == 0)
	{
		side_point.x = ((int)tile_ref.x + 1) * TILE_SIZE;
		side_point.y = (int)tile_ref.y * TILE_SIZE;
	}
	else if (cardinal_direction == NW || cardinal_direction == W || cardinal_direction == N)
	{
		side_point.x = (int)tile_ref.x * TILE_SIZE;
		side_point.y = (int)tile_ref.y * TILE_SIZE;
	}
	else if (cardinal_direction == SE)
	{
		side_point.x = ((int)tile_ref.x + 1) * TILE_SIZE;
		side_point.y = ((int)tile_ref.y + 1) * TILE_SIZE;
	}
	else if (cardinal_direction == SW || cardinal_direction == S)
	{
		side_point.x = (int)tile_ref.x * TILE_SIZE;
		side_point.y = ((int)tile_ref.y + 1) * TILE_SIZE;
	}
	//printf("cardinal_direction:%d\n", cardinal_direction);
	//printf("side_point: %f, %f\n",side_point.x, side_point.y);
	return (side_point);
}