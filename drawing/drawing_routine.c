#include "../c3d.h"

void drawing_routine(t_c3d *c3d)
{
    mlx_destroy_image(c3d->mlx_connection, c3d->map.img);
    create_visualize_2d_map_img(c3d);
    mlx_destroy_image(c3d->mlx_connection, c3d->scene_3d.img);
    draw_2d_fov_boundaries(c3d); 
    draw_3d_scene(c3d);
}   