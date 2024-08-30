#include "../c3d.h"


int step_management(t_point *position, t_move move)
{
    if(move.up)
    {
        position->y -= FOOT_STEP;
        return (HAS_MOVED_UP);
    }
    else if(move.down)
    {
        position->y += FOOT_STEP;
        return (HAS_MOVED_UP);
    }
    else if(move.left)
    {
        position->x -= FOOT_STEP;
        return (HAS_MOVED_UP);
    }
    else if(move.right)
    {
        position->x += FOOT_STEP;
        return (HAS_MOVED_UP);
    }
    return (DID_NOT_MOVE_UP);
}

/*this functions save the position of the player in a tmp variable.
Then works on this last variable.
It first update the coordinate of this point depending on step_management function.
Then it checks if the new point is a collision or not.
if everything was ok, the player position is update with the new valuse.
This function is also the occasion to update the tile where the player is in.*/
int moving(t_move move, t_point *player_position, t_c3d *c3d)
{
    t_point position_to_check;
    
    position_to_check = *player_position;
    if (step_management(&position_to_check, move))
    {
        if(!is_collision(position_to_check.x, position_to_check.y, c3d))
        {
            *player_position = position_to_check;
            c3d->player.tile = tile_reference(*player_position);
            return (HAS_MOVED_UP);
        }
    }
    return (DID_NOT_MOVE_UP);
}

/*
metto il check perchè altrimenti stampa in loop ogni volta con destory e ristamp mappa
invece cosi lo fa solo se c'eè stato un cambiamento

This function colled from "update_player_movement" which in turn
is colled from mlx_loop_hook.
Well, it checks if one of the properties of player-position has been set to 1.
Remember that these are set to 1 from the  function key_press_player_position.
Remeber also that this  last (key_press_player_alpha_rotation) is called from key_press
which is called from
mlx_hook(c3d.win.mlx_win, 2, 1L << 0, key_press, &c3d), with second argument 2 which
indicates the management of press.
If there is a collision simpli don't do anything. so don't update coordinates of player.

*/
int update_position(void *param) 
{
    t_c3d   *c3d;
    int does_it_move;
      
    does_it_move = 0;
    c3d = (t_c3d *)param;   
    if (moving(c3d->player.move, &c3d->player.position,  c3d))
        does_it_move = YES;
    if (does_it_move == YES)
        drawing_routine(c3d);
    return (0); 
}






