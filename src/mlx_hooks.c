/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:14:28 by minsepar          #+#    #+#             */
/*   Updated: 2024/04/04 21:19:19 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	terminate_program(t_mlx *graphic)
{
	mlx_destroy_image(graphic->mlx, graphic->img_data[0].img);
	mlx_destroy_image(graphic->mlx, graphic->img_data[1].img);
	exit(0);
}

static void	on_escape(t_mlx *graphic)
{
	mlx_destroy_window(graphic->mlx, graphic->win);
	terminate_program(graphic);
}

int	key_down(int keypress, void *param)
{
	t_mlx	*graphic;

	graphic = (t_mlx *) param;
	if (keypress == 53)
		on_escape(graphic);
	return (0);
}
