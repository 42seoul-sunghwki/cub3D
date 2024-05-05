/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_jump_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 00:02:20 by minsepar          #+#    #+#             */
/*   Updated: 2024/05/05 13:06:26 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	handle_jump(t_mlx *graphic, t_user *user)
{
	(void) graphic;
	user->z_velocity += user->z_gravity;
	user->z += user->z_velocity;
	if (user->z < 0)
	{
		user->z = 0;
		user->flag &= ~JUMP;
		user->z_velocity = -1;
	}
}
