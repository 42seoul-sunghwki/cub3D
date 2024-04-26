/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_slice_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:42:39 by sunghwki          #+#    #+#             */
/*   Updated: 2024/04/26 17:08:50 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	slice_wall_cub(char **split, t_mlx *mlx, t_block *block)
{
	static char	*wall[6] = {"NO", "SO", "EA", "WE", "CI", "FI"};
	int			i;

	i = -1;
	while (++i < 6)
	{
		if (ft_strncmp(split[0], wall[i], 3) == 0)
		{
			if (check_img_cub(split, mlx, &(block->pic[i])) == FAIL)
				return (FAIL);
			return (SUCCESS);
		}
	}
	return (UNDEFINED);
}

static int	slice_color_cub(char **split, t_block *block)
{
	if (ft_strncmp(split[0], "F", 2) == 0)
	{
		block->f_trgb = color_cub(split);
		if (block->f_trgb == UNDEFINED)
			return (FAIL);
	}
	else if (ft_strncmp(split[0], "C", 2) == 0)
	{
		block->c_trgb = color_cub(split);
		if (block->c_trgb == UNDEFINED)
			return (FAIL);
	}
	else
		return (UNDEFINED);
	return (SUCCESS);
}

/**
 * read folder as count number of files
*/
char		*read_folder_token(DIR *dir)
{
	struct dirent	*entry;
	int				len;

	while (1)
	{
		entry = readdir(dir);
		if (entry == NULL || entry->d_type == DT_REG)
			break ;
	}
	if (entry)
	{
		len = entry->d_namlen;
		if (len > 4 && ft_strncmp(entry->d_name + len - 4, ".xpm", 4) == 0)
			return (ft_strdup(entry->d_name));
	}
	return (NULL);
}

char	*join_path(char *path, char *dir_name)
{
	char	*dir_path;
	char	*tmp;

	tmp = ft_strjoin(path, "/");
	dir_path = ft_strjoin(tmp, dir_name);
	free(tmp);
	return (dir_path);
}

static void	read_folder(char *path, char *dir_name, int num, t_mlx *mlx)
{
	char	*dir_path;
	char	*token;
	char	*file_name;
	int		i;
	DIR		*dir;

	dir_path = join_path(path, dir_name);
	dir = open_folder(dir_path);
	mlx->sprite[num].num_img = count_folder_file(dir);
	mlx->sprite[num].img = (t_pic *)malloc(sizeof(t_pic)
			* mlx->sprite[num].num_img);
	while (1)
	{
		token = read_folder_token(dir);
		if (!token)
			break ;
		file_name = join_path(dir_path, token);
		i = ft_atoi(token) - 1;
		if (i < 0 || i >= mlx->sprite[num].num_img)
			ft_exit("Invalid sprite file name");
		mlx->sprite[num].img[i].name = ft_strdup(file_name);
		printf(("num : %d, i : %d file_name : %s\n"), num, i, file_name);
		check_img_sprite_file(file_name, mlx, &(mlx->sprite[num].img[i]));
		free(token);
		free(file_name);
	}
	closedir(dir);
	free(dir_path);
}

void	slice_sprite_zombie(char **split, t_mlx *mlx)
{
	DIR		*dir;

	if (split[0] == NULL || split[1] == NULL
		|| split[2] != NULL)
		ft_exit("Sprite input is not valid");
	dir = open_folder(split[1]);
	closedir(dir);
	read_folder(split[1], ATTACK, ZOM_ATTACK, mlx);
	read_folder(split[1], DIE, ZOM_DIE, mlx);
	read_folder(split[1], IDLE, ZOM_IDLE, mlx);
	read_folder(split[1], WALK, ZOM_WALK, mlx);
}

void	slice_sprite_door(char **split, t_mlx *mlx)
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

static int	slice_sprite_cub(char **split, t_mlx *mlx)
{
	static char	*sp[4] = {"ZO", "DO", "ME", "GU"};
	int			i;

	i = -1;
	while (++i < 4)
	{
		if (ft_strncmp(split[0], sp[i], 3) == 0)
		{
			if (i == 0)
			{
				slice_sprite_zombie(split, mlx);
				return (SUCCESS);
			}
			if (i == 1)
			{
				slice_sprite_door(split, mlx);
				return (SUCCESS);
			}
		}
	}
	return (UNDEFINED);
}

int	slice_cub(char *line, t_mlx *mlx, t_block *block)
{
	char	**split;

	split = ft_split(line, ' ');
	if (!split)
		return (FAIL);
	if (split[0] == NULL || split[0][0] == '\0')
	{
		free_2d_ptr(split);
		return (SUCCESS);
	}
	if (slice_wall_cub(split, mlx, block) == SUCCESS || \
		slice_sprite_cub(split, mlx) == SUCCESS || \
		slice_color_cub(split, block) == SUCCESS)
	{
		free_2d_ptr(split);
		return (SUCCESS);
	}
	else
	{
		free_2d_ptr(split);
		return (UNDEFINED);
	}
}
