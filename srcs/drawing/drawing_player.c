#include "c3d.h"

/*disegna un pallino sulal mappa.
il pallino essendo una circonferenza ha un raggio.
Infatti nelle iterazioni io itero da -radius (ovvero la metà opposta del diametro)
fino a radius (sia lugo le x che lungo le y).
ma non vado a colorare pixel per pixel altrimenti otterrei un quadrato.
Color, invece, solo quei punto per i quali è soddisfatta l'equazone della circonferenza.*/
void draw_player(t_c3d *c3d, t_point center, int radius, int color) 
{
    t_point point;

    point.x = 0;
    point.y = 0;
    point.y = -radius;
    while (point.y <= radius) 
    {
        point.x = -radius;
        while (point.x <= radius) 
        {
            if (pow(point.x, 2) + pow(point.y , 2) <= radius * radius) /*si tratta di colorare anche il cerchio interno e non solo la circonferenza ecco perchè uso minore anche*/
                mlx_pixel_put(c3d->mlx_connection, c3d->win_2d.mlx_win, center.x + point.x, center.y + point.y, color);
            point.x++;
        }
        point.y++;
    }
}

/*this print the little sement that come out form the little circumference on 2d map. 
it represent where the olayer is looking at*/
void	draw_player_direction(t_c3d *c3d, int x0, int y0, double alpha, int color) 
{
	int x1;
	int y1;
	
	x1 = x0 + RAY_LENGTH * cos(alpha);
	y1 = y0 + RAY_LENGTH * sin(alpha);
	bresenham(c3d, x0, y0, x1, y1, color);
}

void	draw_player_in_img(t_c3d *c3d)
{
	int radius = RADIUS;
    t_point point;

    point.x = 0;
    point.y = 0;
    point.y = -radius;
    while (point.y <= radius) 
    {
        point.x = -radius;
        while (point.x <= radius) 
        {
            if (pow(point.x, 2) + pow(point.y , 2) <= radius * radius) /*si tratta di colorare anche il cerchio interno e non solo la circonferenza ecco perchè uso minore anche*/
            {
				put_pixel(&c3d->map, 	c3d->player.position.x + point.x, c3d->player.position.y + point.y, BLACK);
			   // mlx_pixel_put(c3d->mlx_connection, c3d->win_2d.mlx_win, center.x + point.x, center.y + point.y, color);
			 }
			  point.x++;
        }
        point.y++;
    }
}