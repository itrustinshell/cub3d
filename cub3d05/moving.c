
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
    int mx;
    int my;

    mx = 0;
    my = 0;
    int check = 0;

    int tmp_player_x;
    int tmp_player_y;

    c3d = (t_c3d *)param;
    tmp_player_x = c3d->player.x;
    tmp_player_y = c3d->player.y;
    if (c3d->player.move_up)
    {   
        /*
        sembra che possa avicinarsi il cento del cerchio al margine...poi avviene la 
        sottrazione ....è queindi viene riportato a
        qindi ad esempio viene reimpostata a my + site_tile + radius.
        Ma da questo momento è ad una certa distanza...
        per la qule può fare uno ste di 5 e andare
        */
        mx = c3d->player.x / TILE_SIZE;
        my = (c3d->player.y - FOOT_STEP) / TILE_SIZE;
        if ((c3d->map_fm_file.grid[my][mx]) == '1')
        {
            int limit = (my * TILE_SIZE) + TILE_SIZE;
            if ((c3d->player.y - FOOT_STEP) - limit <= RADIUS) 
            {
                c3d->player.x =  c3d->player.x;
                c3d->player.y =  my * TILE_SIZE + TILE_SIZE + RADIUS;
            }        
        }
        else
            c3d->player.y -= FOOT_STEP;
        check = 1;
    }
    if (c3d->player.move_down)
    {
        mx = c3d->player.x / TILE_SIZE;
        my = (c3d->player.y + FOOT_STEP) / TILE_SIZE;
        if ((c3d->map_fm_file.grid[my][mx]) != '0')
        {
            int limit = (my * TILE_SIZE);            
            if ((limit - (c3d->player.y + FOOT_STEP)) <= RADIUS)
            {
                c3d->player.x =  c3d->player.x;
                c3d->player.y =  limit - RADIUS - 2;
            }        
        }
        else
        {  c3d->player.y += FOOT_STEP;
        
        }
        check = 1;
    }
    if (c3d->player.move_left)
    {
        mx = (c3d->player.x - FOOT_STEP) / TILE_SIZE;
        my = c3d->player.y / TILE_SIZE;
        if ((c3d->map_fm_file.grid[my][mx]) == '1')
        {
            int limit = (mx * TILE_SIZE) + TILE_SIZE;
            if ((c3d->player.x - FOOT_STEP) - limit <= RADIUS) 
            {
                c3d->player.x =  mx * TILE_SIZE + TILE_SIZE + RADIUS;   
                c3d->player.y =  c3d->player.y;
            }        
        }
        else
            c3d->player.x -= FOOT_STEP;
        check = 1;
    }
    if (c3d->player.move_right)
    {  
        mx = (c3d->player.x + FOOT_STEP) / TILE_SIZE; 
        my = c3d->player.y / TILE_SIZE;
        
        if ((c3d->map_fm_file.grid[my][mx]) != '0')
        {
            int limit = (mx * TILE_SIZE);            
            if ((limit - (c3d->player.x + FOOT_STEP)) <= RADIUS)
            {
                
                c3d->player.x =  limit - RADIUS - 2;
                c3d->player.y =  c3d->player.y;
            }        
        }
        else
            c3d->player.x += FOOT_STEP;
        check = 1;
    }
    /*check_if_player_hit_a_wall.
    If so don't update....
    */


//    if ((c3d->map_fm_file.grid[my][mx]) == '1')
//    {
//       c3d->player.x =  tmp_player_x;
//       c3d->player.y =  tmp_player_y;
//    }
   
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
