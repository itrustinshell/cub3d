#include "../cub3d.h"
#include <string.h>

//calculation_of_temporarySX( c3d->map_fm_file.w, ray->DxTemp, ray->DyTemp, alpha);


double    calculation_of_temporarySX_SY(int map_length, double DxTemp, double DyTemp, double alpha, char *chose_sx_or_sy)
{
    double sx_or_sy_to_return;
    
    sx_or_sy_to_return = 0;
    if (strcmp(chose_sx_or_sy, "sx") == 0)
    {
        if (alpha == (M_PI / 2) || alpha == (3 * M_PI / 2))
            sx_or_sy_to_return = DyTemp / sin(alpha);
        else
            sx_or_sy_to_return = DxTemp / cos(alpha);
        if (fabs(sx_or_sy_to_return) > (map_length * TILE_SIZE))
            sx_or_sy_to_return = map_length * TILE_SIZE; //qui ho ridotto molto perchè erano lunghezze enormi man mano che ci si avvicinava a pi/2 ma vedi ora come gestire
        printf("calculation temporarySX %f\n", fabs(sx_or_sy_to_return));
    }
    else
    {
        if (alpha == (M_PI) || alpha == (2 * M_PI) || alpha == (0))
         sx_or_sy_to_return = DxTemp / cos(alpha);
        else
            sx_or_sy_to_return = DyTemp / sin(alpha);
        if (fabs(sx_or_sy_to_return) > (map_length * TILE_SIZE))
            sx_or_sy_to_return = map_length * TILE_SIZE; //qui ho ridotto molto perchè erano lunghezze enormi man mano che ci si avvicinava a pi/2 ma vedi ora come gestire
        printf("calculation temporarySY %f\n",  fabs(sx_or_sy_to_return));
    }
    return (fabs(sx_or_sy_to_return));
}



//dato una certa ipotenusa Sx ottenuta mediante un aumento con Dx mi calcolo i punti estremi della fine di Sx laddove il punto di partenza è smepre il player
t_point calculation_of_end_point_to_check_along_SxTemp(t_c3d *c3d, t_ray *ray, double alpha)
{
    t_point point_to_return;

    point_to_return.x = 0;
    point_to_return.y = 0;

    ray->DxTemp = abs(ray->dx) + TILE_SIZE; //allora aumentiamo di TILE_SIZE il dx. Andiamo a salvare questo valroe in un DXtemporaneo
    printf("DxTemp = %d\n", ray->DxTemp);
    ray->SxTemp =  calculation_of_temporarySX_SY(c3d->map_fm_file.w, ray->DxTemp, ray->DyTemp, alpha, "sx");     //grazie al dx_temporaneo calcolato possiamo calcolarci il nuovi SXtemporaneo           
    point_to_return.x = c3d->player.coordinates.x + fabs(ray->SxTemp) * cos(alpha); //grazie al calcolo del sx temporaneo ecco che posso calcoalrre il nuovo punto
    point_to_return.y = c3d->player.coordinates.y + fabs(ray->SxTemp) * sin(alpha);
    printf("end_point_to_check: (%d, %d)\n", (int)point_to_return.x, (int)point_to_return.y);
    printf("cella di impatto: %d, %d\n", (int)point_to_return.x / TILE_SIZE, (int)point_to_return.y / TILE_SIZE);

    return (point_to_return);
}

//dato una certa ipotenusa Sy ottenuta mediante un aumento con Dy mi calcolo i punti estremi della fine di Sy laddove il punto di partenza è smepre il player
t_point calculation_of_end_point_to_check_along_SyTemp(t_c3d *c3d, t_ray *ray, double alpha)
{
    t_point point_to_return;

    point_to_return.x = 0;
    point_to_return.y = 0;
    ray->DyTemp = abs(ray->dy) + TILE_SIZE; //aumento di TILE_SIZE
    printf("DyTemp = %d\n", ray->DyTemp);
    ray->SyTemp =  calculation_of_temporarySX_SY(c3d->map_fm_file.w, ray->DxTemp, ray->DyTemp, alpha, "sy"); 
    point_to_return.x = c3d->player.coordinates.x + fabs(ray->SyTemp) * cos(alpha);
    point_to_return.y = c3d->player.coordinates.y + fabs(ray->SyTemp) * sin(alpha);
    printf("end_point_to_check:(%d, %d)\n", (int)point_to_return.x, (int)point_to_return.y);
    printf("cella di impatto:: %d, %d\n", (int)point_to_return.x / TILE_SIZE, (int)point_to_return.y / TILE_SIZE);             
    return (point_to_return);

}
