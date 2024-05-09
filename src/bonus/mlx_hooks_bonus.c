/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:14:28 by minsepar          #+#    #+#             */
/*   Updated: 2024/05/09 13:11:52 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	terminate_program(t_mlx *graphic)
{
	t_p_queue	*open_list;
	t_p_queue	*close_list;
	int			i;

	i = -1;
	while (++i < graphic->sprite_vec.size)
	{
		open_list = &graphic->sprite_vec.list[i]->open_list;
		close_list = &graphic->sprite_vec.list[i]->close_list;
		sanitize_p_queue(open_list);
		sanitize_p_queue(close_list);
	}
	exit(0);
}
