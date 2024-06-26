/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_read_sprite_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 19:11:43 by sunghwki          #+#    #+#             */
/*   Updated: 2024/05/09 13:01:22 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static char	*read_folder_token(DIR *dir)
{
	struct dirent	*entry;
	int				len;
	static char		ds_store[] = ".DS_Store";

	len = ft_strlen(ds_store);
	while (1)
	{
		entry = readdir(dir);
		if (entry == NULL)
			break ;
		if (entry->d_type == DT_REG
			&& ft_strncmp(entry->d_name, ds_store, len) != 0)
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

static char	*join_path(char *path, char *dir_name)
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

static void	read_folder_helper(DIR *dir, char *dir_path, int num, t_mlx *mlx)
{
	char	*token;
	char	*file_name;
	int		i;

	while (1)
	{
		token = read_folder_token(dir);
		if (!token)
			break ;
		file_name = join_path(dir_path, token);
		i = ft_atoi(token) - 1;
		if (i < 0 || i >= mlx->sprite[num].num_img)
			ft_exit("Out of range in sprite img");
		check_img_sprite_file(file_name, mlx, &(mlx->sprite[num].img[i]));
		free(token);
		free(file_name);
	}
}

void	read_folder(char *path, char *dir_name, int num, t_mlx *mlx)
{
	char	*dir_path;
	DIR		*dir;

	dir_path = join_path(path, dir_name);
	dir = open_folder(dir_path);
	if (dir == NULL)
		ft_exit("Not valid folder name");
	mlx->sprite[num].num_img = count_folder_file(dir);
	if (mlx->sprite[num].num_img == 0)
		ft_exit("Not input sprite");
	mlx->sprite[num].img = (t_pic *)calloc(mlx->sprite[num].num_img,
			sizeof(t_pic));
	mlx->sprite[num].folder_name = ft_strdup(dir_path);
	read_folder_helper(dir, dir_path, num, mlx);
	closedir(dir);
	free(dir_path);
}
