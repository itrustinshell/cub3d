
#include "cub3d.h"

int key_press(int keycode, void *param) 
{
    t_c3d   *c3d;

    c3d = (t_c3d *)param;
    if (keycode == KEY_W)
        c3d->player.move_up = 1;
    if (keycode == KEY_S)
        c3d->player.move_down = 1;
    if (keycode == KEY_A)
       c3d->player.move_left = 1;
    if (keycode == KEY_D)
        c3d->player.move_right = 1;
    return (0);
}

int key_release(int keycode, void *param) 
{
    t_c3d   *c3d;

    c3d = (t_c3d *)param;
    if (keycode == KEY_W)
        c3d->player.move_up = 0;
    if (keycode == KEY_S)
        c3d->player.move_down = 0;
    if (keycode == KEY_A)
       c3d->player.move_left = 0;
    if (keycode == KEY_D)
        c3d->player.move_right = 0;
    return (0);
}

/*
questa funzione è chiamata da loop_hook nel main
e resta in ascolto continuamente sulle proprietà
del player move_up, move_right_move_left ecc..
Se ueste proprietà sono settate a 1 da qaualche parte allora la funzione aggiorna le 
coordinate del player.
Tale settaggio avviene in key_press e key_release
*/
int update_position(void *param) 
{
    t_c3d   *c3d;

    int check = 0;

    int tmp_player_x;
    int tmp_player_y;


    c3d = (t_c3d *)param;
    tmp_player_x = c3d->player.x;
    tmp_player_y = c3d->player.y;
    if (c3d->player.move_up)
    {   
        c3d->player.y -= FOOT_STEP;
        check = 1;
    }
    if (c3d->player.move_down)
    {
        c3d->player.y += FOOT_STEP;
        check = 1;
    }
    if (c3d->player.move_left)
    {
        c3d->player.x -= FOOT_STEP;
        check = 1;
    }
    if (c3d->player.move_right)
    {
        c3d->player.x += FOOT_STEP;
        check = 1;
    }
    /*check_if_player_hit_a_wall.
    If so don't update....
    */
   int mx;
   int my;
   mx = c3d->player.x / TILE_SIZE;
   my = c3d->player.y / TILE_SIZE;

   if ((c3d->map_fm_file.grid[my][mx]) == '1')
   {
      c3d->player.x =  tmp_player_x;
      c3d->player.y =  tmp_player_y;
   }
   
    if (check == 1)
    {
        mlx_destroy_image(c3d->win.mlx_connection, c3d->img.map_img);
        c3d->img.map_img = mlx_new_image(c3d->win.mlx_connection, c3d->map_fm_file.w * TILE_SIZE, c3d->map_fm_file.h * TILE_SIZE);
        c3d->img.data_img = mlx_get_data_addr(c3d->img.map_img, &c3d->img.bits_per_pixel, &c3d->img.size_line, &c3d->img.endian);
        draw_map(c3d);
        mlx_put_image_to_window(c3d->win.mlx_connection, c3d->win.mlx_win, c3d->img.map_img, 0, 0);

        draw_player(c3d, c3d->player.x, c3d->player.y, RADIUS);
        printf("sto stampando mappa e giocatore\n");
    }
   // printf("sto stampando mappa e giocatore\n");
    return (0); 
}
