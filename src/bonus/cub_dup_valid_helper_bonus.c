/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_dup_valid_helper_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 10:58:21 by sunghwki          #+#    #+#             */
/*   Updated: 2024/05/08 14:04:18 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	cub_dup_valid_sprite_helper(t_mlx *mlx, int i)
{
	t_sprite	*sprite;
	int			j;
	int			len;

	j = -1;
	sprite = &mlx->sprite[i];
	while (++j < sprite->num_img)
	{
		//printf("sprite_name : %s, sprite amount :%d, i : %d\n", sprite->folder_name, sprite->num_img, j);
		if (sprite->img[j].data.img == NULL)
			ft_exit("Not enough sprite image");
	}
	j = -1;
	while (++j < i)
	{
		len = ft_strlen(sprite->folder_name);
		if (mlx->sprite[j].folder_name != NULL
			&& ft_strncmp(mlx->sprite[j].folder_name,
				sprite->folder_name, len) == 0)
			ft_exit("Duplicate sprite");
	}
}

static void	cub_valid_sprite_door(t_mlx *mlx)
{
	t_sprite	*sprite;

	sprite = mlx->sprite;
	if (sprite[DOOR_CLOSE].img != NULL
		&& sprite[DOOR_OPEN].img != NULL)
		return ;
	else
		ft_exit("Not input door sprite");
}

static void	cub_valid_sprite_pepsi(t_mlx *mlx)
{
	t_sprite	*sprite;

	sprite = mlx->sprite;
	if (sprite[PEPSI_DRAW].img != NULL
		&& sprite[PEPSI_IDLE].img != NULL
		&& sprite[PEPSI_DRINK].img != NULL
		&& sprite[PEPSI_OPEN_AND_DRINK].img != NULL
		&& sprite[PEPSI_RUN].img != NULL
		&& sprite[PEPSI_WALK].img != NULL)
		return ;
	else
		ft_exit("Not input user sprite");
}

void	cub_dup_valid_sprite(t_mlx *mlx)
{
	int			i;

	i = -1;
	while (++i < NUM_SPRITE)
	{
		if (mlx->sprite[i].img != NULL)
			cub_dup_valid_sprite_helper(mlx, i);
	}
	cub_valid_sprite_pepsi(mlx);
	cub_valid_sprite_door(mlx);
}
