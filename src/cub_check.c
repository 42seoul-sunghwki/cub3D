/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 19:23:08 by sunghwki          #+#    #+#             */
/*   Updated: 2024/04/09 19:40:50 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_img_cub(char **split, t_mlx *graphic, t_pic *org_img)
{
	if (split[0] == NULL || split[1] == NULL || split[2] != NULL)
	{
		perror("Error\nInvalid cub file");
		exit (1);
	}
	org_img->data.img = mlx_xpm_file_to_image(graphic->mlx, split[1],
			&org_img->w, &org_img->h);
	if (!org_img->data.img)
	{
		perror("Error\nInvalid cub file in img");
		exit (1);
	}
	return (SUCCESS);
}

int	check_map_cub(char *line)
{
	int	i;
	int	flag;

	i = -1;
	flag = 0;
	while (line[++i])
	{
		if (line[i] != ' ')
		{
			flag = 1;
			continue ;
		}
		if (line[i] == ' ' && flag == 1)
			return (FAIL);
		if (line[i] != '1' && line[i] != '0')
			return (FAIL);
		if (line[i] != 'D' && line[i] != 'N'
			&& line[i] != 'S' && line[i] != 'W' && line[i] == 'E')
			return (FAIL);
	}
	return (SUCCESS);
}
