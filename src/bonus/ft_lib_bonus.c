/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lib_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:27:04 by sunghwki          #+#    #+#             */
/*   Updated: 2024/04/14 13:40:07 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_sanitize_enter(char *line)
{
	int		i;

	i = ft_strlen(line);
	if (line[i - 1] == '\n')
		line[i - 1] = '\0';
	return (SUCCESS);
}

void	ft_exit(char *str)
{
	printf("Error\n%s\n", str);
	exit (1);
}
