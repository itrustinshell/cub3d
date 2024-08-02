
#include "cub3d.h"

// int my_key_hook(int keycode, void *param)
// {
//     t_c3d   *c3d;
//     c3d = (t_c3d *)param;

//     if (keycode == 13) //w
//     {
//        // clear_current_drawing(c3d->win.mlx_connection, c3d->win.mlx_win, c3d->win.w, c3d->win.h);
//         c3d->player.y--;
//        // design_map(c3d->win.mlx_connection, c3d->win.mlx_win, 0, 0, c3d->map.grid, c3d->map.w, c3d->map.h);
//        	draw_filled_circle(c3d, c3d->player.x, c3d->player.y, 3, RED);
//     }
//     if (keycode == 0) //a
//     {
//      //   clear_current_drawing(c3d->win.mlx_connection, c3d->win.mlx_win, c3d->win.w, c3d->win.h);
//         c3d->player.x--;
//        // design_map(c3d->win.mlx_connection, c3d->win.mlx_win, 0, 0, c3d->map.grid, c3d->map.w, c3d->map.h);
//        	draw_filled_circle(c3d, c3d->player.x, c3d->player.y, 3, RED);
//     }
//     if (keycode == 2) //d
//     {
//     //    clear_current_drawing(c3d->win.mlx_connection, c3d->win.mlx_win, c3d->win.w, c3d->win.h);
//         c3d->player.x++;
//        // design_map(c3d->win.mlx_connection, c3d->win.mlx_win, 0, 0, c3d->map.grid, c3d->map.w, c3d->map.h);
//        	draw_filled_circle(c3d, c3d->player.x, c3d->player.y, 3, RED);
//     }
//     if (keycode == 1) //s
//     {
//        // clear_current_drawing(c3d->win.mlx_connection, c3d->win.mlx_win, c3d->win.w, c3d->win.h);
//         c3d->player.y++;
//        // design_map(c3d->win.mlx_connection, c3d->win.mlx_win, 0, 0, c3d->map.grid, c3d->map.w, c3d->map.h);
//        	draw_filled_circle(c3d, c3d->player.x, c3d->player.y, 3, RED);
//     }
//     return (0);
// }

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
    return 0;
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
    return 0;
}


// Funzione per aggiornare la posizione dell'oggetto
int update_position(void *param) 
{
    t_c3d   *c3d;

    c3d = (t_c3d *)param;
    if (c3d->player.move_up)
        c3d->player.y -= FOOT_STEP;
    if (c3d->player.move_down)
        c3d->player.y += FOOT_STEP;
    if (c3d->player.move_left)
        c3d->player.x -= FOOT_STEP;
    if (c3d->player.move_right)
        c3d->player.x += FOOT_STEP;

   // mlx_clear_window(c3d->win.mlx_connection, c3d->win.mlx_win);
   // design_map(c3d->win.mlx_connection, c3d->win.mlx_win, 0, 0, c3d->map.grid, c3d->map.w, c3d->map.h);

    draw_filled_circle(c3d, c3d->player.x, c3d->player.y, 3, RED);
    //mlx_circle(c3d->win.mlx_connection, c3d->win.mlx_win, c3d->player.x, c3d->player.y, 3, RED);

    return 0;
}
