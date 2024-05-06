/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_slice_sprite_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 15:44:46 by sunghwki          #+#    #+#             */
/*   Updated: 2024/05/06 20:09:59 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	slice_sprite_pepsi(char **split, t_mlx *mlx)
{
	DIR		*dir;

	if (split[0] == NULL || split[1] == NULL
		|| split[2] != NULL)
		ft_exit("Sprite input is not valid");
	dir = open_folder(split[1]);
	closedir(dir);
	read_folder(split[1], DRAW, 15, mlx);
	read_folder(split[1], IDLE, 16, mlx);
	read_folder(split[1], DRINK, 17, mlx);
	read_folder(split[1], OPEN_AND_DRINK, 18, mlx);
	read_folder(split[1], RUN, 19, mlx);
	read_folder(split[1], WALK, 20, mlx);
}

static void	slice_sprite_door(char **split, t_mlx *mlx)
{
	DIR		*dir;

	if (split[0] == NULL || split[1] == NULL
		|| split[2] != NULL)
		ft_exit("Sprite input is not valid");
	dir = open_folder(split[1]);
	closedir(dir);
	read_folder(split[1], OPEN, DOOR_OPEN, mlx);
	read_folder(split[1], CLOSE, DOOR_CLOSE, mlx);
}

static void	slice_sprite_bear(char **split, t_mlx *mlx)
{
	DIR		*dir;

	if (split[0] == NULL || split[1] == NULL
		|| split[2] != NULL)
		ft_exit("Sprite input is not valid");
	dir = open_folder(split[1]);
	closedir(dir);
	read_folder(split[1], "", DANCING_BEAR, mlx);
}

static void	slice_sprite_dog(char **split, t_mlx *mlx)
{
	DIR		*dir;

	if (split[0] == NULL || split[1] == NULL
		|| split[2] != NULL)
		ft_exit("Sprite input is not valid");
	dir = open_folder(split[1]);
	closedir(dir);
	read_folder(split[1], "", DANCING_DOG, mlx);
}

static void	slice_sprite_cat(char **split, t_mlx *mlx)
{
	DIR		*dir;

	if (split[0] == NULL || split[1] == NULL
		|| split[2] != NULL)
		ft_exit("Sprite input is not valid");
	dir = open_folder(split[1]);
	closedir(dir);
	read_folder(split[1], "", DANCING_CAT, mlx);
}

int	slice_sprite_cub(char **split, t_mlx *mlx)
{
	static char	*sp[] = {"DO", "DB", "DC", "DD", "PS"};
	int			i;

	i = -1;
	while (++i < 5)
	{
		if (ft_strncmp(split[0], sp[i], 3) == 0)
		{
			if (i == 0)
			{
				slice_sprite_door(split, mlx);
				return (SUCCESS);
			}
			else if (i == 1)
			{
				slice_sprite_bear(split, mlx);
				return (SUCCESS);
			}
			else if (i == 2)
			{
				slice_sprite_cat(split, mlx);
				return (SUCCESS);
			}
			else if (i == 3)
			{
				slice_sprite_dog(split, mlx);
				return (SUCCESS);
			}
			else if (i == 4)
			{
				slice_sprite_pepsi(split, mlx);
				return (SUCCESS);
			}
		}
	}
	return (UNDEFINED);
}
