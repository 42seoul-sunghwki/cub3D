/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 19:23:08 by sunghwki          #+#    #+#             */
/*   Updated: 2024/05/09 19:12:30 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_img_cub(char **split, t_mlx *graphic, t_pic *org_img)
{
	int	fd;

	if (split[0] == NULL || split[1] == NULL || split[2] != NULL)
		ft_exit("Invalid cub file");
	fd = open(split[1], O_RDONLY);
	if (fd == -1)
		ft_exit("Invalid cub file in img");
	close(fd);
	if (org_img->data.img != NULL)
		ft_exit("Duplicate img");
	org_img->data.img = mlx_xpm_file_to_image(graphic->mlx, split[1],
			&org_img->w, &org_img->h);
	if (!org_img->data.img)
		ft_exit("Invalid cub file in img");
	get_img_addr(&org_img->data);
	org_img->name = ft_strdup(split[1]);
	return (SUCCESS);
}

int	check_map_cub(char *line)
{
	int	i;
	int	flag;

	i = -1;
	while (line[++i])
	{
		flag = FAIL;
		if (line[i] == ' ')
			continue ;
		if (line[i] == '1' || line[i] == '0')
			flag = SUCCESS;
		if (line[i] == 'N'
			|| line[i] == 'S' || line[i] == 'W' || line[i] == 'E')
			flag = SUCCESS;
		if (flag == FAIL)
			ft_exit("Invalid map using not valid value");
	}
	return (SUCCESS);
}
