#include "../cub3d.h"

/*this function manages the release of movement's player keycode
it is called by key_release which is the call-back function managed by mlx_hook
*/
void    key_release_player_position(int keycode, t_c3d *c3d)
{    
    if (keycode == KEY_W)
        c3d->player.move.up = 0;
    if (keycode == KEY_S)
        c3d->player.move.down = 0;
    if (keycode == KEY_A)
       c3d->player.move.left = 0;
    if (keycode == KEY_D)
        c3d->player.move.right = 0;
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

/*this function has to be this sign becouse it is called in mlx_hook*/
int key_release(int keycode, void *param) 
{
    t_c3d   *c3d;

    c3d = (t_c3d *)param;
    key_release_player_position(keycode, c3d);
    key_release_player_alpha_rotation(keycode, c3d);
    return (0);
}
