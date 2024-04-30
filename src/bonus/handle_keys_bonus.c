/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 20:26:20 by minsepar          #+#    #+#             */
/*   Updated: 2024/04/30 17:59:41 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	handle_keys_loop(t_mlx *graphic)
{
	t_user	*user;

	user = &graphic->user;
	if ((graphic->key_states[A] && !graphic->key_states[D])
		|| (graphic->key_states[D] && !graphic->key_states[A])
		|| (graphic->key_states[W] && !graphic->key_states[S])
		|| (graphic->key_states[S] && !graphic->key_states[W]))
	{
		graphic->user_state = STATE_WALK;
		graphic->weapon_start_frame = 0;
		check_collision(graphic);
	}
	else
	{
		graphic->user_state = STATE_IDLE;
		graphic->weapon_start_frame = 0;
	}
	if (user->flag & JUMP)
		handle_jump(graphic, user);
}
