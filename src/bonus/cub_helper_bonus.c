/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_helper_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 19:36:02 by sunghwki          #+#    #+#             */
/*   Updated: 2024/04/16 13:10:39 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

char	*merge_split(char **split, int start)
{
	char	*ret;
	char	*tmp;
	int		i;
	int		end;

	end = 0;
	i = start - 1;
	ret = ft_strdup(split[start]);
	while (split[end] == NULL)
		end++;
	while (++i < end - 1)
	{
		tmp = ft_strjoin(ret, split[i + 1]);
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

char	**split_to_rgb(char **split)
{
	char	**rgb;
	char	*tmp;
	int		i;

	tmp = merge_split(split, 1);
	if (!tmp)
		return (NULL);
	i = 0;
	while (split[++i] != NULL)
	{
		free(split[i]);
		split[i] = NULL;
	}
	rgb = ft_split(tmp, ',');
	if (!rgb)
		return (NULL);
	free(tmp);
	return (rgb);
}

int	color_cub(char **split)
{
	char	**rgb;
	int		ret;
	int		r;
	int		g;
	int		b;

	rgb = split_to_rgb(split);
	if (!rgb)
		return (UNDEFINED);
	if (rgb[0] == NULL || rgb[1] == NULL || rgb[2] == NULL || rgb[3] != NULL)
	{
		printf("Error\nInvalid cub file\n");
		exit (1);
	}
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	ret = create_trgb(0, r, g, b);
	free_2d_ptr(rgb);
	return (ret);
}
