#include "c3d.h"

/*
this function manage the variation of angle
In particular it calculates how much degree is a variation in rotation.
This function manage also the complete rotations of 360°.
Indeed the angle is expressed in M_PI
So one degree is M_PI / 360.
Well when you press the arrow left or right de degree are subctract or added.
This means that after a complete round if you continue to add they
don't starto from zero again. Or in the opposite direction they will go 
under zero continuing subctracting.
So this function manage this cases so that whrn you reach zero or 360 from left or right
the angle will restart from 360 or 0.
To make a faster rotation you should decrese the denominator to calculate degree.

*/
static void set_rotation(t_c3d *c3d, int *check)
{
    if (c3d->player.rotate_alpha_right)
    {
        c3d->player.direction += DEGREE;
        if (c3d->player.direction > 2 * M_PI)
            c3d->player.direction = c3d->player.direction - (2 * M_PI);
        *check = 1;
    }
    else if (c3d->player.rotate_alpha_left)
    {
        c3d->player.direction -= DEGREE;
         if (c3d->player.direction < 0)
            c3d->player.direction = 2 * M_PI + c3d->player.direction;
        *check = 1;
    }
}

/*
metto il check perchè altrimenti stampa in loop ogni volta con destory e ristamp mappa
invece cosi lo fa solo se c'eè stato un cambiamento

This function colled from "update_player_movement" whichi in turn
is colled from mlx_loop_hook.
Well, it checks if one of the properties of player-rotation has been set to 1.
Remember that these are set to 1 from the  function key_press_player_alpha_rotation.
Remeber also that this  last (key_press_player_alpha_rotation) is called from 
key_press, which is called from
mlx_hook(c3d.win.mlx_win, 2, 1L << 0, key_press, &c3d), with second argument 2 which
indicates the management of press.
This function is useful even becouse it updates perpendicular_direction of player and its
left_half and right_half of the fov.
*/
int update_alpha_rotation(void *param)
{
    t_c3d *c3d;
    int check;

    c3d = (t_c3d *)param;
    check = 0;
    set_rotation(c3d, &check);
    c3d->player.perpendicular_direction = c3d->player.direction - (M_PI / 2); //update perpedicular
    /*#TESTING TEESTING## SE VUOI VEDERE LA retta perpendicolare alla direzionedel giocatore
    tieni rivelata la seguente funzione*/
    //draw_line(c3d->player.position, c3d->player.perpendicular_direction, RED, c3d);
    c3d->player.fov.half_left = c3d->player.direction - (FOV_ANGLE / 2); //update fov half left
	c3d->player.fov.half_right = c3d->player.direction + (FOV_ANGLE / 2); //update fov half right
    if (check == 1)
        drawing_routine(c3d);
    return (0);
}

