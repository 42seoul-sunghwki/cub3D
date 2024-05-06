/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_user_util_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 23:05:04 by minsepar          #+#    #+#             */
/*   Updated: 2024/05/05 20:34:10 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	change_weapon(t_mlx *graphic)
{
	graphic->weapon_num = graphic->change_weapon_num;
	graphic->user_state = STATE_DRAW;
	graphic->weapon_start_frame = graphic->total_frame;
	if (graphic->weapon_num == 1)
		graphic->pepsi_open = 0;
}

void	change_state(t_mlx *graphic, int user_state)
{
	graphic->weapon_start_frame = graphic->total_frame;
	graphic->user_state = user_state;
}
