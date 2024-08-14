#include "../cub3d.h"
#include <string.h>

//dato una certa ipotenusa Sx ottenuta mediante un aumento con Dx mi calcolo i punti estremi della fine di Sx laddove il punto di partenza è smepre il player
t_point calculation_of_end_point_along_path_x(t_c3d *c3d, t_ray *ray, double path, double alpha)
{
	t_point point_to_return;

	point_to_return.x = 0;
	point_to_return.y = 0;
	ray->dx = fabs(ray->dx) + TILE_SIZE; /*allora aumentiamo di TILE_SIZE il dx. Andiamo a salvare questo valroe in un DXtemporaneo*/printf("dx = %f\n", ray->dx);
  
	point_to_return.x = c3d->player.coordinates.x + round(fabs(path) * cos(alpha)); //grazie al calcolo del sx temporaneo ecco che posso calcoalrre il nuovo punto
	point_to_return.y = c3d->player.coordinates.y + round(fabs(path) * sin(alpha)); printf("end_point_to_check: (%d, %d)\n", (int)point_to_return.x, (int)point_to_return.y);printf("cella di impatto: %d, %d\n", (int)point_to_return.x / TILE_SIZE, (int)point_to_return.y / TILE_SIZE);
	return (point_to_return);
}

//dato una certa ipotenusa Sy ottenuta mediante un aumento con Dy mi calcolo i punti estremi della fine di Sy laddove il punto di partenza è smepre il player
t_point calculation_of_end_point_along_path_y(t_c3d *c3d, t_ray *ray, double path, double alpha)
{
	t_point point_to_return;

	point_to_return.x = 0;
	point_to_return.y = 0;
	ray->dy = fabs(ray->dy) + TILE_SIZE; /*aumento di TILE_SIZE*/ printf("dy = %f\n", ray->dy);
	point_to_return.x = c3d->player.coordinates.x + round(fabs(path) * cos(alpha));
	point_to_return.y = c3d->player.coordinates.y + round(fabs(path) * sin(alpha));printf("end_point_to_check:(%d, %d)\n", (int)point_to_return.x, (int)point_to_return.y);printf("cella di impatto:: %d, %d\n", (int)point_to_return.x / TILE_SIZE, (int)point_to_return.y / TILE_SIZE);             
	return (point_to_return);
}
