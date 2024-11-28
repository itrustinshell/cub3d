/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving_main_direction.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpennisi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 20:58:33 by lpennisi          #+#    #+#             */
/*   Updated: 2024/11/27 14:59:20 by lpennisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c3d.h"

void	move_face_north(t_move move, t_point *position)
{
	if (move.w)
		position->y -= FOOT_STEP;
	if (move.s)
		position->y += FOOT_STEP;
	if (move.a)
		position->x -= FOOT_STEP;
	if (move.d)
		position->x += FOOT_STEP;
}

void	move_face_south(t_move move, t_point *position)
{
	if (move.w)
		position->y += FOOT_STEP;
	if (move.s)
		position->y -= FOOT_STEP;
	if (move.a)
		position->x += FOOT_STEP;
	if (move.d)
		position->x -= FOOT_STEP;
}

void	move_face_east(t_move move, t_point *position)
{
	if (move.w)
		position->x += FOOT_STEP;
	if (move.s)
		position->x -= FOOT_STEP;
	if (move.a)
		position->y -= FOOT_STEP;
	if (move.d)
		position->y += FOOT_STEP;
}

void	move_face_west(t_move move, t_point *position)
{
	if (move.w)
		position->x -= FOOT_STEP;
	if (move.s)
		position->x += FOOT_STEP;
	if (move.a)
		position->y += FOOT_STEP;
	if (move.d)
		position->y -= FOOT_STEP;
}

void	move_player_mains(int direction, t_move move, t_point *position)
{
	if (direction == N)
		move_face_north(move, position);
	else if (direction == S)
		move_face_south(move, position);
	else if (direction == W)
		move_face_west(move, position);
	else if (direction == E)
		move_face_east(move, position);
	else
		move_player_oblq(direction, move, position);
}