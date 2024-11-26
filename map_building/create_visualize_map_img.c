#include "../c3d.h"


void draw_player_in_img(t_c3d *c3d)
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


void create_visualize_2d_map_img(t_c3d *c3d)
{
	c3d->map.img = mlx_new_image(c3d->mlx_connection, c3d->raw_map.dimension.width * TILE_SIZE, c3d->raw_map.dimension.heigth * TILE_SIZE);
	c3d->map.data_addr = mlx_get_data_addr(c3d->map.img, &c3d->map.bits_per_pixel, &c3d->map.size_line, &c3d->map.endian);
	draw_2d_map(&c3d->map, c3d); //a questo punto il charone ha disegnata lamappa....ora il charone lo passo a drow player per fargli colorare il playerone sopra
	
	
	// while(y < c3d->map.img_dimension.heigth)
	// {
	// 	while(x <c3d->map.img_dimension.width)
	// 	{		


	// 	}


	// }


	draw_player_in_img(c3d);	
	mlx_put_image_to_window(c3d->mlx_connection, c3d->win_2d.mlx_win, c3d->map.img, 0, 0);

	//draw_2d_fov_boundaries(c3d); 
	/*TODO inserire in qualche modo questo drow nel charone...come fa draw_map...cosi da stamparlo a img
	per ora qui l'ho messo dopo put image altrimenti veniva sovrascritto dall'immagines*/

}
