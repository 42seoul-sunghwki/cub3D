/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:04:13 by sunghwki          #+#    #+#             */
/*   Updated: 2024/04/13 13:31:50 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*read_cub(int fd, t_mlx *graphic)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		printf("line : %s\n", line);
		if (!line)
			break ;
		if (line[0] == '\n')
		{
			free(line);
			continue ;
		}
		if (ft_sanitize_enter(line) == FAIL)
		{
			printf("Error\nEnd of File before Map\n");
			exit(1);
		}
		if (slice_cub(line, graphic, &(graphic->block)) == UNDEFINED)
			return (line);
		free(line);
	}
	return (NULL);
}
