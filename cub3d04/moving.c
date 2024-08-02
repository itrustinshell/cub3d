
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

    c3d = (t_c3d *)param;
    //actual_grid

    //int prev_x = c3d->player.x / TILE_SIZE;
    //int prev_y = c3d->player.y / TILE_SIZE;

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
    
    //capisci in che cella sei e ridisegnala....
    //come lo capisco ...
    //hai una coorinata in un piano creato ad hoc che va da 0 a 50 perchè
    /*
    la tua mappa reale è di 5 x 5 ma ahi messo la piasterlla a 5
    un pixel corrisponde a 5
    se sei alla posizione 1 ebebn
    se sei alla posizione 45 sei alla cella 4
    se sei all'oridnata 34 sei alla cella di ordinata 3
    in pratica dividendo la tua coordinata per un numero int...tu ottieni la cella
    quindi funziona cosi...dividi la cooridnata o ascisa del giocatore per x size 
    e passi quella alla funzioe droaw

    */
    
    //actual_tile
    int current_x = c3d->player.x / TILE_SIZE;
    int current_y = c3d->player.y / TILE_SIZE;

    // int grid_N_x = current_x;
    // int grid_N_y = current_y - 1;
    // int grid_E_x = current_x + 1;
    // int grid_E_y = current_y;
    // int grid_S_x = current_x;
    // int grid_S_y = current_y + 1;
    // int grid_W_x = current_x - 1;
    // int grid_W_y = current_y;
    // int grid_NE_x = current_x + 1;
    // int grid_NE_y = current_y - 1;
    // int grid_NW_x = current_x - 1;
    // int grid_NW_y = current_y - 1;
    // int grid_SE_x = current_x + 1;
    // int grid_SE_y = current_y + 1;
    // int grid_SW_x = current_x - 1;
    // int grid_SW_y = current_y + 1;



    draw_tile_with_internal_margin(c3d->win.mlx_connection, c3d->win.mlx_win, current_x * TILE_SIZE, current_y * TILE_SIZE, YELLOW);
    // draw_tile_with_internal_margin(c3d->win.mlx_connection, c3d->win.mlx_win, grid_N_x * TILE_SIZE, grid_N_y * TILE_SIZE, YELLOW);
    // draw_tile_with_internal_margin(c3d->win.mlx_connection, c3d->win.mlx_win, grid_S_x * TILE_SIZE, grid_S_y * TILE_SIZE, YELLOW);
    // draw_tile_with_internal_margin(c3d->win.mlx_connection, c3d->win.mlx_win, grid_E_x * TILE_SIZE, grid_E_y * TILE_SIZE, YELLOW);
    // draw_tile_with_internal_margin(c3d->win.mlx_connection, c3d->win.mlx_win, grid_W_x * TILE_SIZE, grid_W_y * TILE_SIZE, YELLOW);
    // draw_tile_with_internal_margin(c3d->win.mlx_connection, c3d->win.mlx_win, grid_NE_x * TILE_SIZE, grid_NE_y * TILE_SIZE, YELLOW);
    // draw_tile_with_internal_margin(c3d->win.mlx_connection, c3d->win.mlx_win, grid_NW_x * TILE_SIZE, grid_NW_y * TILE_SIZE, YELLOW);
    // draw_tile_with_internal_margin(c3d->win.mlx_connection, c3d->win.mlx_win, grid_SE_x * TILE_SIZE, grid_SE_y * TILE_SIZE, YELLOW);
    // draw_tile_with_internal_margin(c3d->win.mlx_connection, c3d->win.mlx_win, grid_SW_x * TILE_SIZE, grid_SW_y * TILE_SIZE, YELLOW);

   
   
   
    draw_filled_circle(c3d, c3d->player.x, c3d->player.y, RADIUS);
 

    //draw_player(c3d, c3d->player.x, c3d->player.y, 3);
    //mlx_circle(c3d->win.mlx_connection, c3d->win.mlx_win, c3d->player.x, c3d->player.y, 3, RED);

    return (0); 
}
