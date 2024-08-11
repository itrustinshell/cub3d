
#include "../cub3d.h"

/*this function has to be this sign becouse it is called in mlx_hook*/
int key_press(int keycode, void *param) 
{
    t_c3d   *c3d;

    c3d = (t_c3d *)param;
    key_press_player_position(keycode, c3d);
    key_press_player_alpha_rotation(keycode, c3d);
    return (0);
}

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
int update_player_movement(void *param)
{
     update_position(param);
     update_alpha_rotation(param);
     return (0);
}
