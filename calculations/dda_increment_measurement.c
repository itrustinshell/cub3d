#include "../cub3d.h"
#include <string.h>


// double calculation_of_temporarySX_SY(int map_length, double deltaX, double deltaY, double alpha, char *chose_sx_or_sy)
// {
//     double sx_or_sy_to_return = 0;
    
//     if (strcmp(chose_sx_or_sy, "sx") == 0)
//     {
//         if (fabs(alpha - M_PI / 2) < EPSILON || fabs(alpha - 3 * M_PI / 2) < EPSILON) //calcolo con epsilon...quindi vd a vedere quando alpha è molto prossima a pigreco -mezzi....sottraendole pigrecomezii verificho se assume un valore molto vicino allo zero...praticamente se è zero. ma in tal modo accetto una tolleranza maggiore. nel sensoc he ci sono angoli minuscoli prissimo allo zero che vengono gestiti
//             sx_or_sy_to_return = deltaY / sin(alpha);
//         else
//             sx_or_sy_to_return = deltaX / cos(alpha);
//     }
//     else
//     {
//         if (fabs(alpha - M_PI) < EPSILON || fabs(alpha - 2 * M_PI) < EPSILON || fabs(alpha) < EPSILON)
//             sx_or_sy_to_return = deltaX / cos(alpha);
//         else
//             sx_or_sy_to_return = deltaY / sin(alpha);
//     }
//     if (fabs(sx_or_sy_to_return) > (map_length * TILE_SIZE))
//         sx_or_sy_to_return = map_length * TILE_SIZE; //qui ho ridotto molto perchè erano lunghezze enormi man mano che ci si avvicinava a pi/2 ma vedi ora come gestire
//     printf("calculation temporarySY %f\n",  fabs(sx_or_sy_to_return));
//     return fabs(sx_or_sy_to_return);
// }

//dato una certa ipotenusa Sx ottenuta mediante un aumento con Dx mi calcolo i punti estremi della fine di Sx laddove il punto di partenza è smepre il player
t_point calculation_of_end_point_to_check_along_path_x(t_c3d *c3d, t_ray *ray, double alpha)
{
    t_point point_to_return;

    point_to_return.x = 0;
    point_to_return.y = 0;

    ray->dx = fabs(ray->dx) + TILE_SIZE; //allora aumentiamo di TILE_SIZE il dx. Andiamo a salvare questo valroe in un DXtemporaneo
    printf("dx = %f\n", ray->dx);
  
    ray->path_x =  calculate_sx_sy(c3d->map_fm_file.w, ray->dx, ray->dy, alpha, "sx");     //grazie al dx_temporaneo calcolato possiamo calcolarci il nuovi path_xoraneo           
    point_to_return.x = c3d->player.coordinates.x + round(fabs(ray->path_x) * cos(alpha)); //grazie al calcolo del sx temporaneo ecco che posso calcoalrre il nuovo punto
    point_to_return.y = c3d->player.coordinates.y + round(fabs(ray->path_x) * sin(alpha));
    printf("end_point_to_check: (%d, %d)\n", (int)point_to_return.x, (int)point_to_return.y);
    printf("cella di impatto: %d, %d\n", (int)point_to_return.x / TILE_SIZE, (int)point_to_return.y / TILE_SIZE);
    return (point_to_return);
}

//dato una certa ipotenusa Sy ottenuta mediante un aumento con Dy mi calcolo i punti estremi della fine di Sy laddove il punto di partenza è smepre il player
t_point calculation_of_end_point_to_check_along_path_y(t_c3d *c3d, t_ray *ray, double alpha)
{
    t_point point_to_return;

    point_to_return.x = 0;
    point_to_return.y = 0;
    ray->dy = fabs(ray->dy) + TILE_SIZE; //aumento di TILE_SIZE
    printf("dy = %f\n", ray->dy);
    ray->path_y =  calculate_sx_sy(c3d->map_fm_file.w, ray->dx, ray->dy, alpha, "sy"); 
    point_to_return.x = c3d->player.coordinates.x + round(fabs(ray->path_y) * cos(alpha));
    point_to_return.y = c3d->player.coordinates.y + round(fabs(ray->path_y) * sin(alpha));
    printf("end_point_to_check:(%d, %d)\n", (int)point_to_return.x, (int)point_to_return.y);
    printf("cella di impatto:: %d, %d\n", (int)point_to_return.x / TILE_SIZE, (int)point_to_return.y / TILE_SIZE);             
    return (point_to_return);
}
