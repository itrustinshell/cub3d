
#include "../cub3d.h"

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
