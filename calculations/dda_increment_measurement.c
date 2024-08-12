#include "../cub3d.h"
#include <string.h>

double    calculation_of_temporarySX(t_c3d *c3d, t_ray *ray, double alpha)
{
    if (alpha == (M_PI / 2) || alpha == (3 * M_PI / 2))
        ray->SxTemp = ray->DyTemp / sin(alpha);
    else
        ray->SxTemp = ray->DxTemp / cos(alpha);
    if (fabs(ray->SxTemp) > (c3d->map_fm_file.w * TILE_SIZE))
        ray->SxTemp= c3d->map_fm_file.w * TILE_SIZE; //qui ho ridotto molto perchè erano lunghezze enormi man mano che ci si avvicinava a pi/2 ma vedi ora come gestire
    printf("calculation temporarySX %f\n", fabs(ray->SxTemp));
    return (fabs(ray->SxTemp));
}

double	calculation_of_temporarySY(t_c3d *c3d,  t_ray *ray, double alpha)
{
	if (alpha == (M_PI) || alpha == (2 * M_PI) || alpha == (0))
         ray->SyTemp = ray->DxTemp / cos(alpha);
	else
        ray->SyTemp = ray->DyTemp / sin(alpha);
	if (fabs(ray->SyTemp) > (c3d->map_fm_file.h * TILE_SIZE))
         ray->SyTemp = c3d->map_fm_file.h * TILE_SIZE; //qui ho ridotto molto perchè erano lunghezze enormi man mano che ci si avvicinava a pi/2 ma vedi ora come gestire
    printf("calculation temporarySY %f\n",  fabs(ray->SyTemp));
	return ( fabs(ray->SyTemp));
}

//dato una certa ipotenusa Sx ottenuta mediante un aumento con Dx mi calcolo i punti estremi della fine di Sx laddove il punto di partenza è smepre il player
void calculation_of_end_point_to_check_along_SxTemp(t_c3d *c3d, t_ray *ray, double alpha)
{
    ray->DxTemp = abs(ray->dx) + TILE_SIZE; //allora aumentiamo di TILE_SIZE il dx. Andiamo a salvare questo valroe in un DXtemporaneo
    printf("DxTemp = %d\n", ray->DxTemp);
    ray->SxTemp = calculation_of_temporarySX(c3d, ray, alpha);     //grazie al dx_temporaneo calcolato possiamo calcolarci il nuovi SXtemporaneo           
    ray->end_point_to_check.x = c3d->player.x + fabs(ray->SxTemp) * cos(alpha); //grazie al calcolo del sx temporaneo ecco che posso calcoalrre il nuovo punto
    ray->end_point_to_check.y = c3d->player.y + fabs(ray->SxTemp) * sin(alpha);
    printf("end_point_to_check: (%d, %d)\n", ray->end_point_to_check.x, ray->end_point_to_check.y);
    printf("cella di impatto: %d, %d\n", ray->end_point_to_check.x / TILE_SIZE, ray->end_point_to_check.y / TILE_SIZE);
}

//dato una certa ipotenusa Sy ottenuta mediante un aumento con Dy mi calcolo i punti estremi della fine di Sy laddove il punto di partenza è smepre il player
void calculation_of_end_point_to_check_along_SyTemp(t_c3d *c3d, t_ray *ray, double alpha)
{
    ray->DyTemp = abs(ray->dy) + TILE_SIZE; //aumento di TILE_SIZE
    printf("DyTemp = %d\n", ray->DyTemp);
    ray->SyTemp = calculation_of_temporarySY(c3d, ray, alpha);
    ray->end_point_to_check.x = c3d->player.x + fabs(ray->SyTemp) * cos(alpha);
    ray->end_point_to_check.y = c3d->player.y + fabs(ray->SyTemp) * sin(alpha);
    printf("end_point_to_check:(%d, %d)\n", ray->end_point_to_check.x, ray->end_point_to_check.y);
    printf("cella di impatto:: %d, %d\n", ray->end_point_to_check.x / TILE_SIZE, ray->end_point_to_check.y / TILE_SIZE);             
}
