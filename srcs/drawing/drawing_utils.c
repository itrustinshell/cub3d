#include "c3d.h"


/*questa funzione va a posizionare il puntatore all'inizio di un colore.
lo casta poi ad int.
in questo modo veranno letto i 4 byte consecutivi come un singolo valore intero
che rappresenterà il colore.
siccome parliamo di byte e codice bianrio avrai un'area di emroia 10010111000110100101010100 
tutta sta roe è il colore.
ricordati che ogni elemento del charone è una componente del colore: 8 bits = 1 byte.
quindi tu qui avanzi di 4 byte in 4 byte (0vvero 8 bits * 4 in 8bits * 4)
*/
int get_pixel(t_img *img, int x, int y)
{
    int *pixel;

	if (x < 0 || x > img->img_dimension.width || y < 0 || y > img->img_dimension.heigth)
		return RED;

    pixel = (int *)(img->data_addr + (y * img->size_line + x * (img->bits_per_pixel / 8)));
	return *pixel;
}

/*put_pixel() parte dalla constatazione che dispongo di un
char * (un array di char, che rappresenta il mio data_Addr della
immagine, in cui sono custoditi i colori).
Sappiamo che i colori sono tuttavia degli int.
Pertanto put_pixel() casta il charone ad array di int (int *).
poi dereferenzia lo stesso per l'assrgnazione del colore, di volta in volta*/
void put_pixel(t_img *img, int x, int y, int color)
{
    int *pixel;
	pixel = (int *)(img->data_addr + (y * img->size_line + x * (img->bits_per_pixel / 8)));
   	*pixel = color;
}

void bresenham(t_c3d *c3d, int x0, int y0, int x1, int y1, int color) 
{
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int sx, sy;

	if (x0 < x1) {
		sx = 1;
	} else {
		sx = -1;
	}

	if (y0 < y1) {
		sy = 1;
	} else {
		sy = -1;
	}

	int err = dx - dy;

	while (1) 
	{
		mlx_pixel_put(c3d->mlx_connection, c3d->win_2d.mlx_win, x0, y0, color);
		// mlx_pixel_put(c3d->win_2d.mlx_connection, c3d->win_3d.mlx_win, x0, y0, color); //for 3d win

		if (x0 == x1 && y0 == y1) break;
		int e2 = 2 * err;
		if (e2 > -dy) {
			err -= dy;
			x0 += sx;
		}
		if (e2 < dx) {
			err += dx;
			y0 += sy;
		}
	}
}
