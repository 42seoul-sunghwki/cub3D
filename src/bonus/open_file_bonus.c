/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:45:07 by sunghwki          #+#    #+#             */
/*   Updated: 2024/05/08 12:20:25 by sunghwki         ###   ########.fr       */
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
	if (!dir)
		ft_exit("Failed to open folder");
	return (dir);
}

int	count_folder_file(DIR *dir)
{
	int				ret;
	int				len;
	struct dirent	*entry;
	static char		ds_store[] = ".DS_Store";

	ret = 0;
	len = ft_strlen(ds_store);
	entry = readdir(dir);
	while (entry)
	{
		if (entry->d_type == DT_REG)
		{
			if (ft_strncmp(entry->d_name, ds_store, len) != 0)
				ret++;
		}
		entry = readdir(dir);
	}
	rewinddir(dir);
	return (ret);
}
