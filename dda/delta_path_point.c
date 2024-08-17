#include "../cub3d.h"
#include <string.h>

/*
Legenda:
deltax = dx (is the distance from prlayer.x to the chosen TILE'side)
deltay = dy
distx = sx (is the hypotenus calculated for a particular dx)
disty = sy
*/

double calculate_deltaX(t_point first_point, t_point second_point, int cardinal_direction)
{
    double deltaX;
    
    deltaX = 0;
    if (cardinal_direction == E)
        deltaX = fabs(second_point.x - first_point.x); 
    else if (cardinal_direction == NE) 
        deltaX = fabs(second_point.x - first_point.x); 
    else if (cardinal_direction == N)
        deltaX = fabs(second_point.x - first_point.x); //V
    else if (cardinal_direction == NW)
        deltaX = fabs(second_point.x - first_point.x - 1);
    else if (cardinal_direction == W )
        deltaX = fabs(second_point.x - first_point.x - 1);
    else if (cardinal_direction == SW)
        deltaX = fabs(second_point.x - first_point.x - 1);
    else if (cardinal_direction == S)
        deltaX = fabs(second_point.x - first_point.x - 1);
    else if (cardinal_direction == SE)
        deltaX = fabs(second_point.x - first_point.x);

    return (deltaX);
}

double calculate_deltaY(t_point first_point, t_point second_point, int cardinal_direction)
{
    double deltaY;
    deltaY = 0;
    if (cardinal_direction == E)
        deltaY = fabs(first_point.y - second_point.y + 1);
    else if (cardinal_direction == NE )
        deltaY = fabs(first_point.y - second_point.y + 1); 
    else if (cardinal_direction == N)
        deltaY = fabs(first_point.y - second_point.y + 1); 
    else if (cardinal_direction == NW)
        deltaY = fabs(first_point.y - second_point.y + 1);
    else if (cardinal_direction == W )
        deltaY = fabs(first_point.y - second_point.y + 1); //dovrebbe essere indifferente se su o giu
    else if (cardinal_direction == SW)
        deltaY = fabs(first_point.y - second_point.y); 
    else if (cardinal_direction == S)
        deltaY = fabs(first_point.y - second_point.y);
    else if (cardinal_direction == SE)
        deltaY = fabs(first_point.y - second_point.y);

    return (deltaY);
}

t_delta calculate_delta(t_point first_point, t_point second_point, int cardinal_direction)
{
    t_delta delta;

    delta.x = 0;
    delta.y = 0;
    delta.x = calculate_deltaX(first_point, second_point, cardinal_direction);
    delta.y = calculate_deltaY(first_point, second_point, cardinal_direction);
    return (delta);
}

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

t_point trigonometric_pointCalculation(t_point point, double path, double alpha)
{
	t_point point_to_return;

	point_to_return.x = 0;
	point_to_return.y = 0;
	point_to_return.x = point.x + round(fabs(path) * cos(alpha)); //grazie al calcolo del sx temporaneo ecco che posso calcoalrre il nuovo punto
	point_to_return.y = point.y + round(fabs(path) * sin(alpha));
	printf("end_point_to_check: (%d, %d)\n", (int)point_to_return.x, (int)point_to_return.y);
	printf("cella di impatto: %d, %d\n", (int)point_to_return.x / TILE_SIZE, (int)point_to_return.y / TILE_SIZE);
	return (point_to_return);
}