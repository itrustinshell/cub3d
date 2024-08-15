#include "../cub3d.h"

t_point trigonometric_pointCalculation(t_point player_position, double path, double alpha)
{
	t_point point_to_return;

	point_to_return.x = 0;
	point_to_return.y = 0;
	point_to_return.x = player_position.x + round(fabs(path) * cos(alpha)); //grazie al calcolo del sx temporaneo ecco che posso calcoalrre il nuovo punto
	point_to_return.y = player_position.y + round(fabs(path) * sin(alpha)); printf("end_point_to_check: (%d, %d)\n", (int)point_to_return.x, (int)point_to_return.y);printf("cella di impatto: %d, %d\n", (int)point_to_return.x / TILE_SIZE, (int)point_to_return.y / TILE_SIZE);
	return (point_to_return);
}
