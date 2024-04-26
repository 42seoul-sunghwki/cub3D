/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keyrelease_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 20:04:16 by minsepar          #+#    #+#             */
/*   Updated: 2024/04/22 20:11:43 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	handle_keyrelease(int keycode, void *arg)
{
	t_mlx	*graphic;

	printf("key released: [%d]\n", keycode);
	graphic = arg;
	graphic->key_states[keycode] = false;
	return (SUCCESS);
}
