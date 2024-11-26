#include "../../c3d.h"

/*disegna la scena 3d: ovvero mette tutto nello stringone:
prima il cielo, poi la terra, e poi i muri...*/
void draw_3d_scene(t_c3d *c3d)
{
	c3d->scene_3d.img_dimension.width = c3d->raw_map.dimension.width * TILE_SIZE;
	c3d->scene_3d.img_dimension.heigth = c3d->raw_map.dimension.heigth * TILE_SIZE;
	c3d->scene_3d.img = mlx_new_image(c3d->mlx_connection,c3d->scene_3d.img_dimension.width, c3d->scene_3d.img_dimension.heigth);
	c3d->scene_3d.data_addr = mlx_get_data_addr(c3d->scene_3d.img, &c3d->scene_3d.bits_per_pixel, &c3d->scene_3d.size_line, &c3d->scene_3d.endian);
	draw_ceiling(c3d);
	draw_floor(c3d);
	draw_3d_fov(c3d);
    mlx_put_image_to_window(c3d->mlx_connection, c3d->win_3d.mlx_win, c3d->scene_3d.img, 0, 0);
}
