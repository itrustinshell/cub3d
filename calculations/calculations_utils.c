#include "../cub3d.h"

double calculate_path(int map_length, double deltaX, double deltaY, double alpha, int chose_path)
{
    double path;

    path = 0;
    if (chose_path == PATH_X)
    {
        if (fabs(alpha - M_PI / 2) < EPSILON || fabs(alpha - 3 * M_PI / 2) < EPSILON) //mettiamo il valore assoluto e vediamo se è minore di EPSILON_ Se lo è significa che è prossimo allo zero
            path = deltaY / sin(alpha);
        else
            path = deltaX / cos(alpha);printf("ipotenusa tramite dx: %f\n", fabs(path));
    }
    else
    {
        if (fabs(alpha - M_PI) < EPSILON || fabs(alpha - 2 * M_PI) < EPSILON || fabs(alpha) < EPSILON)
            path = deltaX / cos(alpha);
        else
            path = deltaY / sin(alpha);printf("ipotenusa tramite dy: %f\n", fabs(path));
    }
    path = fmin(fabs(path), map_length * TILE_SIZE);
    return (fabs(path));
}