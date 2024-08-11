
#include "../cub3d.h"

// /*this function has to be this sign becouse it is called in mlx_hook*/
// static void key_press_player_position(int keycode, t_c3d *c3d)
// {
//     if (keycode == KEY_W)
//         c3d->player.move_up = 1;
//     if (keycode == KEY_S)
//         c3d->player.move_down = 1;
//     if (keycode == KEY_A)
//        c3d->player.move_left = 1;
//     if (keycode == KEY_D)
//         c3d->player.move_right = 1;
// }

// static void key_press_player_alpha_rotation(int keycode, t_c3d *c3d)
// {
//     if (keycode == ARROW_LEFT)
//         c3d->player.alpha_direction_left = 1;
//     if (keycode == ARROW_RIGHT)
//         c3d->player.alpha_direction_right = 1;
// }

/*this function has to be this sign becouse it is called in mlx_hook*/
int key_press(int keycode, void *param) 
{
    t_c3d   *c3d;

    c3d = (t_c3d *)param;
    key_press_player_position(keycode, c3d);
    key_press_player_alpha_rotation(keycode, c3d);
    return (0);
}

// /*this function manages the release of movement's player keycode*/
// static void    key_release_player_position(int keycode, t_c3d *c3d)
// {    
//     if (keycode == KEY_W)
//         c3d->player.move_up = 0;
//     if (keycode == KEY_S)
//         c3d->player.move_down = 0;
//     if (keycode == KEY_A)
//        c3d->player.move_left = 0;
//     if (keycode == KEY_D)
//         c3d->player.move_right = 0;
// }

// /*this function manages the release of rotaionn of player's alpha direction
// which is where the player is looking at in a particular moment*/
// void    key_release_player_alpha_rotation(int keycode, t_c3d *c3d)
// {
//     if (keycode == ARROW_LEFT)
//         c3d->player.alpha_direction_left = 0;
//     if (keycode == ARROW_RIGHT)
//         c3d->player.alpha_direction_right = 0;
// }

/*this function has to be this sign becouse it is called in mlx_hook*/
int key_release(int keycode, void *param) 
{
    t_c3d   *c3d;

    c3d = (t_c3d *)param;
    key_release_player_position(keycode, c3d);
    key_release_player_alpha_rotation(keycode, c3d);
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
    int check;
      
    check = 0;
    c3d = (t_c3d *)param;   
    if (c3d->player.move_up)
    {   
        if(!is_collision(c3d->player.x, c3d->player.y - FOOT_STEP, c3d))
        {
            c3d->player.y -= FOOT_STEP;
            check = 1;
        }
    }
    if (c3d->player.move_down)
    {
        if(!is_collision(c3d->player.x, c3d->player.y + FOOT_STEP, c3d))
        {
            c3d->player.y += FOOT_STEP;
            check = 1;
        }   
    }
    if (c3d->player.move_left)
    {
        if(!is_collision(c3d->player.x - FOOT_STEP, c3d->player.y, c3d))
        {
            c3d->player.x -= FOOT_STEP;
            check = 1;
        }   
    }
    if (c3d->player.move_right)
    {  
        if(!is_collision(c3d->player.x + FOOT_STEP, c3d->player.y, c3d))
        {
            c3d->player.x += FOOT_STEP;
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
        
        draw_line(c3d->win.mlx_connection, c3d->win.mlx_win, c3d->player.x, c3d->player.y, c3d->player.alpha_direction, BLACK);

        printf("sto stampando mappa e giocatore\n");
    }
   // printf("sto stampando mappa e giocatore\n");
    return (0); 
}

/*
metto il check perchè altrimenti stampa in loop ogni volta con destory e ristamp mappa
invece cosi lo fa solo se c'eè stato un cambiamento
*/
int update_alpha_direction(void *param)
{
    t_c3d *c3d;
    int check;

    c3d = (t_c3d *)param;
    check = 0;
    if (c3d->player.rotate_alpha_right)
    {
        c3d->player.alpha_direction += 0.1;
        check = 1;
    }
    if (c3d->player.rotate_alpha_left)
    {
        c3d->player.alpha_direction -= 0.1;
        check = 1;
    }
    if (check == 1)
    {
        mlx_destroy_image(c3d->win.mlx_connection, c3d->img.map_img);
        c3d->img.map_img = mlx_new_image(c3d->win.mlx_connection, c3d->map_fm_file.w * TILE_SIZE, c3d->map_fm_file.h * TILE_SIZE);
        c3d->img.data_img = mlx_get_data_addr(c3d->img.map_img, &c3d->img.bits_per_pixel, &c3d->img.size_line, &c3d->img.endian);
        draw_map(c3d);
        mlx_put_image_to_window(c3d->win.mlx_connection, c3d->win.mlx_win, c3d->img.map_img, 0, 0);

        draw_player(c3d, c3d->player.x, c3d->player.y, RADIUS);
        printf("this is alpha: %f\n", c3d->player.alpha_direction);
        draw_line(c3d->win.mlx_connection, c3d->win.mlx_win, c3d->player.x, c3d->player.y, c3d->player.alpha_direction, BLACK);

        static int loop_test;
        printf("sto stampando %d\n", loop_test);
        loop_test++;
    }
    
    return (0);
}


int update(void *param)
{
     update_position(param);
     update_alpha_direction(param);
     return (0);
}
