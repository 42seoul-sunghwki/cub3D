/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_helper_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 19:22:28 by sunghwki          #+#    #+#             */
/*   Updated: 2024/05/06 19:22:46 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	init_minimap(t_pic *minimap)
{
	minimap->h = WINWIDTH / MINIMAP_SCALE;
	minimap->w = WINWIDTH / MINIMAP_SCALE;
}
