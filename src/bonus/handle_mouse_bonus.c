/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mouse_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 15:56:15 by minsepar          #+#    #+#             */
/*   Updated: 2024/04/17 14:42:11 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d_bonus.h"

int	handle_mouse_click(int button, int x, int y, void *arg)
{
	t_mlx	*graphic;

	graphic = arg;
	(void) graphic;
	printf("button :[%d]\n", button);
	printf("x: [%d] y: [%d]\n", x, y);
	return (0);
}
