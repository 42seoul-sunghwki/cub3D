/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_dup_valid.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 16:06:51 by sunghwki          #+#    #+#             */
/*   Updated: 2024/04/10 16:18:27 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		cub_img_dup_valid(t_pic *org, t_pic *cmp)
{
	int 	i;
	char	*org_img;
	char	*cmp_img;

	if (org->h != cmp->h || org->w != cmp->w)
		return (FAIL);
	org_img = org->data.img;
	cmp_img = cmp->data.img;
	i = -1;
	while (++i < org->data.size)
	{
		if (org_img[i] != cmp_img[i])
			return (FAIL);
	}
}

void	cub_dup_valid(t_mlx *mlx)
{
	
}
