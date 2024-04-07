/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 15:56:15 by minsepar          #+#    #+#             */
/*   Updated: 2024/04/07 15:59:29 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

int	handle_mouse(int button, int x, int y, void *arg)
{
	t_mlx	*graphic;

	graphic = arg;
	printf("button :[%d]\n", button);
	printf("x: [%d] y: [%d]\n", x, y);
	return(0);
}
