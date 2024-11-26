#include "c3d.h"


/*questa funzione è la stessa di circle...semplicemente la racchiude
in modo che è più semplice leggere draw_player che drwa_filled_circle*/
void    draw_player(t_c3d *c3d, t_point player_position, int radius, int color)
{
    draw_filled_circle(c3d, player_position, radius, color);
}

/*this print the little sement that come out form the little circumference on 2d map. 
it represent where the olayer is looking at*/
void draw_player_direction(t_c3d *c3d, int x0, int y0, double alpha, int color) 
{
	int x1;
	int y1;
	
	x1 = x0 + RAY_LENGTH * cos(alpha);
	y1 = y0 + RAY_LENGTH * sin(alpha);
	bresenham(c3d, x0, y0, x1, y1, color);
}