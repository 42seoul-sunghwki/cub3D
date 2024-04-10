/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lib.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:27:04 by sunghwki          #+#    #+#             */
/*   Updated: 2024/04/10 14:28:08 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_sanitize_enter(char *line)
{
	int		i;

	i = ft_strlen(line);
	if (i == 0)
		return (line);
	if (line[i - 1] == '\n')
		line[i - 1] = '\0';
	return (line);
}
