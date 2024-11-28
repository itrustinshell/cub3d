/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving_oblq_direction.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpennisi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 21:00:44 by lpennisi          #+#    #+#             */
/*   Updated: 2024/11/27 14:59:43 by lpennisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c3d.h"

void	move_face_north_east(t_move move, t_point *position)
{
	if (move.w)
	{
		position->y -= FOOT_STEP;
		position->x += FOOT_STEP;
	}
	if (move.s)
	{
		position->y += FOOT_STEP;
		position->x -= FOOT_STEP;
	}
	if (move.a)
	{
		position->x -= FOOT_STEP;
		position->y -= FOOT_STEP;
	}
	if (move.d)
	{
		position->x += FOOT_STEP;
		position->y += FOOT_STEP;
	}
}

void	move_face_north_west(t_move move, t_point *position)
{
	if (move.w)
	{
		position->y -= FOOT_STEP;
		position->x -= FOOT_STEP;
	}
	if (move.s)
	{
		position->y += FOOT_STEP;
		position->x += FOOT_STEP;
	}
	if (move.a)
	{
		position->x -= FOOT_STEP;
		position->y += FOOT_STEP;
	}
	if (move.d)
	{
		position->x += FOOT_STEP;
		position->y -= FOOT_STEP;
	}
}

void	move_face_south_east(t_move move, t_point *position)
{
	if (move.w)
	{
		position->y += FOOT_STEP;
		position->x += FOOT_STEP;
	}
	if (move.s)
	{
		position->y -= FOOT_STEP;
		position->x -= FOOT_STEP;
	}
	if (move.a)
	{
		position->x += FOOT_STEP;
		position->y -= FOOT_STEP;
	}
	if (move.d)
	{
		position->x -= FOOT_STEP;
		position->y += FOOT_STEP;
	}
}

void	move_face_south_west(t_move move, t_point *position)
{
	if (move.w)
	{
		position->y += FOOT_STEP;
		position->x -= FOOT_STEP;
	}
	if (move.s)
	{
		position->y -= FOOT_STEP;
		position->x += FOOT_STEP;
	}
	if (move.a)
	{
		position->x += FOOT_STEP;
		position->y += FOOT_STEP;
	}
	if (move.d)
	{
		position->x -= FOOT_STEP;
		position->y -= FOOT_STEP;
	}
}

void	move_player_oblq(int direction, t_move move, t_point *position)
{
	if (direction == NE)
		move_face_north_east(move, position);
	else if (direction == NW)
		move_face_north_west(move, position);
	else if (direction == SE)
		move_face_south_east(move, position);
	else if (direction == SW)
		move_face_south_west(move, position);
}