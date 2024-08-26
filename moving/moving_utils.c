#include "../cub3d.h"


t_point tile_reference(t_point point)
{
    t_point tile_reference;

    tile_reference.x = 0;
    tile_reference.y = 0;

    tile_reference.x = (int)(point.x / TILE_SIZE);
    tile_reference.y = (int)(point.y / TILE_SIZE);

    return (tile_reference);
}

//attenzione dovendo passare un puntatore di puntatori in questa funzione,
//qualora accedessi al data address tramit il parametro passato t_c3d *crd
//devi scrivvere cosi: draw_map(&(c3d)->map.data_addr, c3d); Solo questo uso 
//delle parentesi funziona. draw_map(&(c3d)->map.data_addr, c3d) non funziona.



void stuff_to_draw( t_c3d *c3d)
{
    //t_point end_point;
    mlx_destroy_image(c3d->mlx_connection, c3d->map.img);

    c3d->map.img = mlx_new_image(c3d->mlx_connection, c3d->raw_map.dimension.width * TILE_SIZE, c3d->raw_map.dimension.heigth * TILE_SIZE);
    c3d->map.data_addr = mlx_get_data_addr(c3d->map.img, &c3d->map.bits_per_pixel, &c3d->map.size_line, &c3d->map.endian);
    draw_2d_map(&(c3d->map), c3d);

    mlx_put_image_to_window(c3d->mlx_connection, c3d->win_2d.mlx_win, c3d->map.img, 0, 0);
    // mlx_put_image_to_window(c3d->win_2d.mlx_connection, c3d->win_3d.mlx_win, c3d->img.map_img, 0, 0); //per il 3D

    draw_player(c3d, c3d->player.position, RADIUS, RED);
    //draw_player_direction(c3d, c3d->player.position.x, c3d->player.position.y, c3d->player.direction, BLACK);
   	//dda(c3d->player.position, c3d->player.direction, c3d);
    mlx_clear_window(c3d->mlx_connection, c3d->win_3d.mlx_win);
    draw_2d_fov_boundaries(c3d); //TODO inserire in qualche modo questo drow nel charone...come fa draw_map...cosi da stamparlo a img

    draw_field_of_view(c3d);
    //draw_player_direction(c3d, c3d->player.position.x, c3d->player.position.y, c3d->player.direction, BLACK);
   // end_point = dda(c3d->player.position, c3d->player.direction, c3d);
    //find_x_texture( end_point);


}