/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_slice_sprite_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 15:44:46 by sunghwki          #+#    #+#             */
/*   Updated: 2024/05/05 16:53:25 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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

	if (dir_name[0] == '\0')
	{
		return (ft_strdup(path));
	}
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
		//printf(("num : %d, i : %d file_name : %s\n"), num, i, file_name);
		check_img_sprite_file(file_name, mlx, &(mlx->sprite[num].img[i]));
		free(token);
		free(file_name);
	}
	closedir(dir);
	free(dir_path);
}

static void	slice_sprite_zombie(char **split, t_mlx *mlx)
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
	static char	*sp[] = {"ZO", "DO", "ME", "GU", "DB", "DD", "DC", "PS"};
	int			i;

	i = -1;
	while (++i < 8)
	{
		if (ft_strncmp(split[0], sp[i], 3) == 0)
		{
			if (i == 0)
			{
				slice_sprite_zombie(split, mlx);
				return (SUCCESS);
			}
			else if (i == 1)
			{
				slice_sprite_door(split, mlx);
				return (SUCCESS);
			}
			else if (i == 4)
			{
				slice_sprite_bear(split, mlx);
				return (SUCCESS);
			}
			else if (i == 5)
			{
				slice_sprite_dog(split, mlx);
				return (SUCCESS);
			}
			else if (i == 6)
			{
				slice_sprite_cat(split, mlx);
				return (SUCCESS);
			}
			else if (i == 7)
			{
				slice_sprite_pepsi(split, mlx);
				return (SUCCESS);
			}
		}
	}
	return (UNDEFINED);
}
