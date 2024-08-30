#include "../c3d.h"

static void draw_tile_with_internal_margin(t_img *img, int x, int y, int color, t_c3d *c3d)
{
	t_c3d *ciao;
	ciao = c3d;
    int x_value;
    int y_value;

    x_value = x;
    y_value = y;
    while (y < y_value + TILE_SIZE)
    {
        x = x_value;
        while (x < x_value + TILE_SIZE)
        {
            if (y == y_value + TILE_SIZE - 1)
                put_pixel(img, x, y, BLACK);
            else if (x == x_value + TILE_SIZE - 1)
                put_pixel(img, x, y, BLACK);
            else 
                put_pixel(img, x, y, color);
            x++;
        }
        y++;
    }
}

/*questa funzione stampa il confie destro e sinistro del FOV! Punto!

*/
void	draw_2d_fov_boundaries(t_c3d *c3d)
{	
	t_point end_point; /*dichiaro un t_point end_point*/
	point_init(&end_point); /*lo inizializzo*/
	end_point = dda(c3d->player.position, c3d->player.fov.half_left, c3d); /*calcolo
	l'end point in questione con il dda. In tal caso passo la variabile della struct
	fov.half_left. In pratica in ogni momento il giocatore avrà sempre una direzione
	ed avrà sempre un fov ed un half_left e half_rigth aggiornati. Sempre!.
	Questo aggiornamento continuo è possibile grazie alla logica che trovi in: initializaztion
	e in update_rotation. Ad ogni rotazione infatti il valore di fov è aggiornato.
	Infatto si riferisce sempre e solo ad un calcolo effettuato rispetto alal direzione del giocatore.*/
	bresenham(c3d, c3d->player.position.x, c3d->player.position.y, end_point.x, end_point.y, RED);
	end_point = dda(c3d->player.position, c3d->player.fov.half_right, c3d);
	bresenham(c3d, c3d->player.position.x, c3d->player.position.y, end_point.x, end_point.y, RED);
}

/*commentata per lavorare su un'altra cosi da non modificare questa che funziona*/
void	draw_2d_map(t_img *img, t_c3d *c3d)
{
	int starting_drawing_x;
	int starting_drawing_y;
	int x;
	int y;

	starting_drawing_x = 0;
	starting_drawing_y = 0;
	y = starting_drawing_y;
	while (y < starting_drawing_y + c3d->raw_map.dimension.heigth)
	{	
		x = starting_drawing_x; 
		while (x < starting_drawing_x + c3d->raw_map.dimension.width)
		{
			if (c3d->raw_map.grid[y][x] == '1')
				draw_tile_with_internal_margin(img, x * TILE_SIZE, y * TILE_SIZE, GRAY, c3d);			  
			else if (c3d->raw_map.grid[y][x] == '0') 
				draw_tile_with_internal_margin(img, x * TILE_SIZE, y * TILE_SIZE, WHITE, c3d);			
			else 
				draw_tile_with_internal_margin(img, x * TILE_SIZE, y * TILE_SIZE, RED, c3d);
			x++;
		}
		y++;
	}
}


