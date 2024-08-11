#include "../cub3d.h"

/*
metto il check perchè altrimenti stampa in loop ogni volta con destory e ristamp mappa
invece cosi lo fa solo se c'eè stato un cambiamento

This function colled from "update_player_movement" which in turn
is colled from mlx_loop_hook.
Well, it checks if one of the properties of player-position has been set to 1.
Remember that these are set to 1 from the  function key_press_player_position.
Remeber also that this  last (key_press_player_alpha_rotation) is called from key_press
which is called from
mlx_hook(c3d.win.mlx_win, 2, 1L << 0, key_press, &c3d), with second argument 2 which
indicates the management of press.
If there is a collision simpli don't do anything. so don't update coordinates of player.

*/

void update_player_tile_reference(t_c3d* c3d)
{
    c3d->player.tile_x = c3d->player.x / TILE_SIZE;
    c3d->player.tile_y = c3d->player.y / TILE_SIZE;
}

int update_position(void *param) 
{
    t_c3d   *c3d;
    int check;
      
    check = 0;
    c3d = (t_c3d *)param;   
    if (c3d->player.move_up)
    {   
        if(!is_collision(c3d->player.x, c3d->player.y - FOOT_STEP, c3d))
        {
            c3d->player.y -= FOOT_STEP;
            update_player_tile_reference(c3d);
            check = 1;
        }
    }
    if (c3d->player.move_down)
    {
        if(!is_collision(c3d->player.x, c3d->player.y + FOOT_STEP, c3d))
        {
            c3d->player.y += FOOT_STEP;
            update_player_tile_reference(c3d);
            check = 1;
        }   
    }
    if (c3d->player.move_left)
    {
        if(!is_collision(c3d->player.x - FOOT_STEP, c3d->player.y, c3d))
        {
            c3d->player.x -= FOOT_STEP;
            update_player_tile_reference(c3d);
            check = 1;
        }   
    }
    if (c3d->player.move_right)
    {  
        if(!is_collision(c3d->player.x + FOOT_STEP, c3d->player.y, c3d))
        {
            c3d->player.x += FOOT_STEP;
            update_player_tile_reference(c3d);
            check = 1;
        }   
    }
    if (check == 1)
    {
        mlx_destroy_image(c3d->win.mlx_connection, c3d->img.map_img);
        c3d->img.map_img = mlx_new_image(c3d->win.mlx_connection, c3d->map_fm_file.w * TILE_SIZE, c3d->map_fm_file.h * TILE_SIZE);
        c3d->img.data_img = mlx_get_data_addr(c3d->img.map_img, &c3d->img.bits_per_pixel, &c3d->img.size_line, &c3d->img.endian);
        draw_map(c3d);
        mlx_put_image_to_window(c3d->win.mlx_connection, c3d->win.mlx_win, c3d->img.map_img, 0, 0);

        draw_player(c3d, c3d->player.x, c3d->player.y, RADIUS);
        
        draw_2d_player_direction(c3d, c3d->player.x, c3d->player.y, c3d->player.alpha_direction, BLACK);

        printf("sto stampando mappa e giocatore\n");
    }
   // printf("sto stampando mappa e giocatore\n");
    return (0); 
}






