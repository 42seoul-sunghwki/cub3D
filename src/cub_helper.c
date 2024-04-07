/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 19:36:02 by sunghwki          #+#    #+#             */
/*   Updated: 2024/04/07 21:13:52 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*merge_split(char **split, int start)
{
	char	*ret;
	char	*tmp;
	int		i;
	int		end;

	end = 0;
	i = start - 1;
	ret = split[start];
	while (split[end] == NULL)
		end++;
	while (++i < end - 1)
	{
		tmp = ft_strlcat(ret, split[i + 1]);
		if (!tmp)
		{
			free(ret);
			return (NULL);
		}
		free(ret);
		ret = tmp;
	}
	return (ret);
}

int	color_cub(char **split)
{
	char	**rgb;
	int		ret;
	int		r;
	int		g;
	int		b;

	rgb = ft_split(split[1], ',');
	if (!rgb)
		return (UNDEFINED);
	if (rgb[0] == NULL || rgb[1] == NULL || rgb[2] == NULL || rgb[3] != NULL)
	{
		perror("Error\nInvalid cub file");
		free_2d_ptr(rgb);
		return (UNDEFINED);
	}
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	ret = create_trgb(0, r, g, b);
	free_2d_ptr(rgb);
	return (ret);
}

char	**split_line(char *line)
{
	char	**split;

	split = ft_split(line, ' ');
	if (!split)
		return (NULL);
	if (split[0] == NULL)
	{
		free(split);
		return (NULL);
	}
	return (split);
}
