/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 15:56:15 by minsepar          #+#    #+#             */
/*   Updated: 2024/04/13 17:00:19 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_mouse(int button, int x, int y, void *arg)
{
	t_mlx	*graphic;

	graphic = arg;
	(void) graphic;
	printf("button :[%d]\n", button);
	printf("x: [%d] y: [%d]\n", x, y);
	return (0);
}
