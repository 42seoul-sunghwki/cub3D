/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:45:07 by sunghwki          #+#    #+#             */
/*   Updated: 2024/04/13 17:32:22 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	open_file(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_exit("Failed to open file");
	return (fd);
}

int	close_file(int fd)
{
	if (close(fd) == -1)
		ft_exit("Failed to close file");
	return (SUCCESS);
}
