/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:45:07 by sunghwki          #+#    #+#             */
/*   Updated: 2024/04/10 16:00:46 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	open_file(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror("Error\n");
		perror("Failed to open file\n");
		exit(1);
	}
	return (fd);
}

int	close_file(int fd)
{
	if (close(fd) == -1)
	{
		perror("Error\n");
		perror("Failed to close file\n");
		exit(1);
	}
	return (SUCCESS);
}
