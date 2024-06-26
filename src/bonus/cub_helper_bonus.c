/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_helper_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 19:36:02 by sunghwki          #+#    #+#             */
/*   Updated: 2024/05/13 16:04:47 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static char	*merge_split(char **split, int start)
{
	char	*ret;
	char	*tmp;
	int		i;
	int		end;

	end = 0;
	i = start - 1;
	ret = ft_strdup(split[start]);
	while (split[end] != NULL)
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

static void	check_comma_rgb(char *tmp)
{
	int	len;
	int	i;

	len = ft_strlen(tmp);
	i = 0;
	while (len--)
	{
		if (tmp[len] == ',')
			i++;
	}
	if (i != 2)
		ft_exit("Not valid color");
}

static char	**split_to_rgb(char **split)
{
	char	**rgb;
	char	*tmp;
	int		i;

	tmp = merge_split(split, 1);
	if (!tmp)
		return (NULL);
	check_comma_rgb(tmp);
	i = -1;
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

static	int	input_to_rgb(char *str)
{
	int	i;
	int	len;
	int	ret;

	i = -1;
	len = ft_strlen(str);
	if (len > 3)
		ft_exit("Wrong Color over Range");
	while (++i < len)
	{
		if (i == 0 && str[i] == '+')
			continue ;
		if (!ft_isdigit(str[i]))
			ft_exit("Wrong Color Digit");
	}
	ret = ft_atoi(str);
	if (ret < 0 || ret > 255)
		ft_exit("Wrong Color over Range");
	return (ret);
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
		ft_exit("Invalid cub file in color");
	r = input_to_rgb(rgb[0]);
	g = input_to_rgb(rgb[1]);
	b = input_to_rgb(rgb[2]);
	ret = create_trgb(0, r, g, b);
	free_2d_ptr(rgb);
	return (ret);
}
