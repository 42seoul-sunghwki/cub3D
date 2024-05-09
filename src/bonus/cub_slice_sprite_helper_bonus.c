/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_slice_sprite_helper_bonus.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 21:41:13 by sunghwki          #+#    #+#             */
/*   Updated: 2024/05/09 12:50:21 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	slice_sprite_bear(char **split, t_mlx *mlx)
{
	DIR		*dir;

	if (split[0] == NULL || split[1] == NULL
		|| split[2] != NULL)
		ft_exit("Sprite input is not valid");
	dir = open_folder(split[1]);
	closedir(dir);
	read_folder(split[1], "", DANCING_BEAR, mlx);
	free_sprite_img_name(mlx->sprite, DANCING_BEAR);
}

void	slice_sprite_dog(char **split, t_mlx *mlx)
{
	DIR		*dir;

	if (split[0] == NULL || split[1] == NULL
		|| split[2] != NULL)
		ft_exit("Sprite input is not valid");
	dir = open_folder(split[1]);
	closedir(dir);
	read_folder(split[1], "", DANCING_DOG, mlx);
	free_sprite_img_name(mlx->sprite, DANCING_DOG);
}

void	slice_sprite_cat(char **split, t_mlx *mlx)
{
	DIR		*dir;

	if (split[0] == NULL || split[1] == NULL
		|| split[2] != NULL)
		ft_exit("Sprite input is not valid");
	dir = open_folder(split[1]);
	closedir(dir);
	read_folder(split[1], "", DANCING_CAT, mlx);
	free_sprite_img_name(mlx->sprite, DANCING_CAT);
}
