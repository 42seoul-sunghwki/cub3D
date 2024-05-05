/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:14:28 by minsepar          #+#    #+#             */
/*   Updated: 2024/04/30 21:18:36 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	terminate_program(t_mlx *graphic)
{
	// int	i;

	// i = -1;
	(void) graphic;
	// mlx_destroy_image(graphic->mlx, graphic->img_data[0].img);
	// mlx_destroy_image(graphic->mlx, graphic->img_data[1].img);
	// while (++i < 4)
	// {
	// 	mlx_destroy_image(graphic->mlx, graphic->block.pic[i].data.img);
	// }
	// BASS_StreamFree(graphic->sound_stream);
	// BASS_Free();
	exit(0);
}
