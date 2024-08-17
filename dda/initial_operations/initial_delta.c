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