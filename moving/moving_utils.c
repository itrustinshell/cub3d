#include "../cub3d.h"


t_point tile_reference(t_point point)
{
    t_point tile_reference;

    tile_reference.x = 0;
    tile_reference.y = 0;

    tile_reference.x = point.x / TILE_SIZE;
    tile_reference.y = point.y / TILE_SIZE;

    return (tile_reference);
}


void stuff_to_draw(t_c3d *c3d)
{
    mlx_destroy_image(c3d->win.mlx_connection, c3d->img.map_img);
    c3d->img.map_img = mlx_new_image(c3d->win.mlx_connection, c3d->map_fm_file.dimension.width * TILE_SIZE, c3d->map_fm_file.dimension.heigth * TILE_SIZE);
    c3d->img.data_img = mlx_get_data_addr(c3d->img.map_img, &c3d->img.bits_per_pixel, &c3d->img.size_line, &c3d->img.endian);
    draw_map(c3d);
    mlx_put_image_to_window(c3d->win.mlx_connection, c3d->win.mlx_win, c3d->img.map_img, 0, 0);
    draw_player(c3d, c3d->player.position, RADIUS, RED);
    draw_2d_player_direction(c3d, c3d->player.position.x, c3d->player.position.y, c3d->player.alpha_direction, BLACK);
    draw_field_of_view(c3d);
    camera_plane(c3d->player.position, c3d->player.alpha_direction,  c3d);
}