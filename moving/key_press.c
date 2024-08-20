#include "../cub3d.h"

/*this function manages the press of movement's player keycode
it is called by key_press which is the call-back function managed by mlx_hook
*/
void key_press_playerPosition(int keycode, t_c3d *c3d)
{
    if (keycode == KEY_W)
        c3d->player.move.up = 1;
    if (keycode == KEY_S)
        c3d->player.move.down = 1;
    if (keycode == KEY_A)
       c3d->player.move.left = 1;
    if (keycode == KEY_D)
        c3d->player.move.right = 1;
}

/*it is called by key_press which is the call-back function managed by mlx_hook*/
void    key_press_playerDirection(int keycode, t_c3d *c3d)
{
    if (keycode == ARROW_RIGHT)
        c3d->player.rotate_alpha_right = 1;
    if (keycode == ARROW_LEFT)
        c3d->player.rotate_alpha_left = 1;
}

/*this function has to be this sign becouse it is called in mlx_hook*/
int key_press(int keycode, void *param) 
{
    t_c3d   *c3d;

    c3d = (t_c3d *)param;
    key_press_playerPosition(keycode, c3d);
    key_press_playerDirection(keycode, c3d);
    return (0);
}


