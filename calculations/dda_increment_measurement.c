#include "../cub3d.h"
#include <string.h>

//dato una certa ipotenusa Sx ottenuta mediante un aumento con Dx mi calcolo i punti estremi della fine di Sx laddove il punto di partenza è smepre il player
t_point calculate_end_point(t_point player_position, double path, double alpha)
{
	t_point point_to_return;

	point_to_return.x = 0;
	point_to_return.y = 0;
	point_to_return.x = player_position.x + round(fabs(path) * cos(alpha)); //grazie al calcolo del sx temporaneo ecco che posso calcoalrre il nuovo punto
	point_to_return.y = player_position.y + round(fabs(path) * sin(alpha)); printf("end_point_to_check: (%d, %d)\n", (int)point_to_return.x, (int)point_to_return.y);printf("cella di impatto: %d, %d\n", (int)point_to_return.x / TILE_SIZE, (int)point_to_return.y / TILE_SIZE);
	return (point_to_return);
}
