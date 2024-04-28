/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_jump_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 00:02:20 by minsepar          #+#    #+#             */
/*   Updated: 2024/04/28 18:20:29 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	handle_jump(t_mlx *graphic, t_user *user)
{
	(void) graphic;
	//printf("enter handle_jump\n");
	user->z_velocity += user->z_gravity;
	user->z += user->z_velocity;
	//printf("user->z_gravity %f\n", user->z_gravity);
	if (user->z < 0)
	{
		user->z = 0;
		user->flag &= ~JUMP;
		user->z_velocity = -1;
	}
}
