/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:45:07 by sunghwki          #+#    #+#             */
/*   Updated: 2024/04/26 12:32:36 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	open_file(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		printf("Error\nFailed to open file\n");
		exit(1);
	}
	return (fd);
}

int	close_file(int fd)
{
	if (close(fd) == -1)
	{
		printf("Error\nFailed to close file\n");
		exit(1);
	}
	return (SUCCESS);
}

DIR	*open_folder(char *path)
{
	DIR	*dir;

	dir = opendir(path);
	printf("path: %s\n", path);
	if (!dir)
		ft_exit("Failed to open folder");
	return (dir);
}

int	count_folder_file(DIR *dir)
{
	int				ret;
	struct dirent	*entry;

	ret = 0;
	entry = readdir(dir);
	while (entry)
	{
		if (entry->d_type == DT_REG)
			ret++;
		entry = readdir(dir);
	}
	rewinddir(dir);
	return (ret);
}
