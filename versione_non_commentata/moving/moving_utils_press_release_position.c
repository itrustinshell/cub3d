#include "../cub3d.h"

/*this function manages the press of movement's player keycode
it is called by key_press which is the call-back function managed by mlx_hook
*/
void key_press_player_position(int keycode, t_c3d *c3d)
{
    if (keycode == KEY_W)
        c3d->player.move_up = 1;
    if (keycode == KEY_S)
        c3d->player.move_down = 1;
    if (keycode == KEY_A)
       c3d->player.move_left = 1;
    if (keycode == KEY_D)
        c3d->player.move_right = 1;
}

/*this function manages the release of movement's player keycode
it is called by key_release which is the call-back function managed by mlx_hook
*/
void    key_release_player_position(int keycode, t_c3d *c3d)
{    
    if (keycode == KEY_W)
        c3d->player.move_up = 0;
    if (keycode == KEY_S)
        c3d->player.move_down = 0;
    if (keycode == KEY_A)
       c3d->player.move_left = 0;
    if (keycode == KEY_D)
        c3d->player.move_right = 0;
}
