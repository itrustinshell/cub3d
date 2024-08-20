#include "../cub3d.h"




/*this functions receives the movement (up, down, left, right)  of the player (t_move struct), and the reference to
 player position. If the movement is 1 (=HAS_MOVED_UP), then the new position of the
player is updated.
This function is also the occasion to update the tile where the player is in.*/
int move_up(int movement, t_point *player_position, t_c3d *c3d)
{
    if (movement)
    {   
        if(!is_collision(player_position->x, player_position->y - FOOT_STEP, c3d))
        {
            player_position->y -= FOOT_STEP;
	        c3d->player.tile = tile_reference(*player_position);
            return (HAS_MOVED_UP);
        }
    }
    return (DID_NOT_MOVE_UP);
}


/*same logic of move_up*/
int move_down(int movement, t_point *player_position, t_c3d *c3d)
{
    if (movement)
    {
        if(!is_collision(player_position->x, player_position->y + FOOT_STEP, c3d))
        {
            player_position->y += FOOT_STEP;
	        c3d->player.tile = tile_reference(c3d->player.position);
            return (HAS_MOVED_UP);
        }   
    }
    return (DID_NOT_MOVE_UP);
}

/*same logic of move_up*/
int move_left(int movement, t_point *player_position, t_c3d *c3d)
{
    if (movement)
    {
        if(!is_collision(player_position->x - FOOT_STEP, player_position->y, c3d))
        {
            player_position->x -= FOOT_STEP;
	        c3d->player.tile = tile_reference(c3d->player.position);
            return (HAS_MOVED_UP);
        }  
    }
    return (DID_NOT_MOVE_UP);
}

/*same logic of move_up*/
int move_right(int movement, t_point *player_position, t_c3d *c3d)
{
    if (movement)
    {
        if(!is_collision(player_position->x + FOOT_STEP, player_position->y, c3d))
        {
            player_position->x += FOOT_STEP;
	        c3d->player.tile = tile_reference(c3d->player.position);
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
    if(move_up(c3d->player.move.up, &c3d->player.position, c3d))
        does_it_move = YES;
    if(move_down(c3d->player.move.down, &c3d->player.position, c3d))
        does_it_move = YES;
    if(move_left(c3d->player.move.left, &c3d->player.position, c3d))
        does_it_move = YES;
    if(move_right(c3d->player.move.right, &c3d->player.position, c3d))
        does_it_move = YES;
    if (does_it_move == YES)
        stuff_to_draw(c3d);
    return (0); 
}






