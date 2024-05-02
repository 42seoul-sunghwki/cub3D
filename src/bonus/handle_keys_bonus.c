/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 20:26:20 by minsepar          #+#    #+#             */
/*   Updated: 2024/04/30 23:13:45 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

bool	check_need_move(t_mlx *graphic)
{
	if ((graphic->key_states[A] && !graphic->key_states[D])
		|| (graphic->key_states[D] && !graphic->key_states[A])
		|| (graphic->key_states[W] && !graphic->key_states[S])
		|| (graphic->key_states[S] && !graphic->key_states[W]))
		return (true);
	return (false);
}

void	set_run_state(t_mlx *graphic)
{
	t_user	*user;

	user = &graphic->user;
	user->move_speed = RUN_SPEED;
	change_state(graphic, STATE_RUN);
	play_sound(graphic, RUN_SOUND);
}

void	set_walk_state(t_mlx *graphic)
{
	t_user	*user;

	user = &graphic->user;
	user->move_speed = MOVE_SPEED;
	change_state(graphic, STATE_WALK);
	play_sound(graphic, WALK_SOUND);
}

void	handle_keys_loop(t_mlx *graphic)
{
	t_user	*user;
	int		user_state;

	user = &graphic->user;
	user_state = graphic->user_state;
	if (check_need_move(graphic))
	{
		if (graphic->key_states[SHIFT]
			&& (user_state == STATE_IDLE || user_state == STATE_WALK))
			set_run_state(graphic);
		else if (!graphic->key_states[SHIFT]
			&& (user_state == STATE_IDLE || user_state == STATE_RUN))
			set_walk_state(graphic);
		check_collision(graphic);
	}
	else if (user_state == STATE_WALK || user_state == STATE_RUN)
	{
		change_state(graphic, STATE_IDLE);
		BASS_ChannelStop(graphic->sound_stream[graphic->cur_audio]);
	}
	if (user->flag & JUMP)
		handle_jump(graphic, user);
}
