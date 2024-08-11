#include "../cub3d.h"

/*
it is called by key_press which is the call-back function managed by mlx_hook
*/
void    key_press_player_alpha_rotation(int keycode, t_c3d *c3d)
{
    if (keycode == ARROW_RIGHT)
        c3d->player.rotate_alpha_right = 1;
    if (keycode == ARROW_LEFT)
        c3d->player.rotate_alpha_left = 1;
}

/*this function manages the release of rotaionn of player's alpha direction
which is where the player is looking at in a particular moment.
it is called by key_release which is the call-back function managed by mlx_hook
*/
void    key_release_player_alpha_rotation(int keycode, t_c3d *c3d)
{
    if (keycode == ARROW_RIGHT)
        c3d->player.rotate_alpha_right = 0;
    if (keycode == ARROW_LEFT)
        c3d->player.rotate_alpha_left = 0;
}
