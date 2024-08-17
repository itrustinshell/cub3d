#include "../cub3d.h"

t_path calculate_path(t_delta delta, double alpha) //TODO: Verifica se hai bisogno di fabs
{
    t_path path;

    path.x = 0;
    path.y = 0;

    if (fabs(alpha - M_PI / 2) < EPSILON || fabs(alpha - 3 * M_PI / 2) < EPSILON) //mettiamo il valore assoluto e vediamo se è minore di EPSILON_ Se lo è significa che è prossimo allo zero
        path.x = fabs(delta.y / sin(alpha));
    else
        path.x = fabs(delta.x / cos(alpha));printf("ipotenusa tramite dx: %f\n", fabs(path.x));
 
    if (fabs(alpha - M_PI) < EPSILON || fabs(alpha - 2 * M_PI) < EPSILON || fabs(alpha) < EPSILON)
        path.y = fabs(delta.x / cos(alpha));
    else
        path.y = fabs(delta.y / sin(alpha));printf("ipotenusa tramite dy: %f\n", fabs(path.y));
    return (path);
}