/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_check_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 19:23:08 by sunghwki          #+#    #+#             */
/*   Updated: 2024/04/14 19:01:43 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_img_sprite_file(char **split, t_mlx *graphic, t_pic *org_img)
{
	int	fd;

	fd = open(split[1], O_RDONLY);
	if (fd == -1)
		ft_exit("Img file is not exist");
	close(fd);
	org_img->data.img = mlx_xpm_file_to_image(graphic->mlx, split[1],
			&org_img->w, &org_img->h);
	if (!org_img->data.img)
		ft_exit("Img file is not valid");
	get_img_addr(&org_img->data);
	org_img->name = ft_strdup(split[1]);
}

int	check_img_cub(char **split, t_mlx *graphic, t_pic *org_img)
{
	if (split[0] == NULL || split[1] == NULL || split[2] != NULL)
 		ft_exit("Img input is not valid");
	check_img_sprite_file(split, graphic, org_img);
	return (SUCCESS);
}

int	check_sprite_cub(char **split, t_mlx *graphic,
		t_pic *org_img, t_sprite *sprite)
{
	int	i;

	if (split[0] == NULL || split[1] == NULL
		|| split[2] == NULL || split[3] != NULL)
		ft_exit("Sprite input is not valid");
	check_img_sprite_file(split, graphic, org_img);
	i = -1;
	while (split[2][++i])
	{
		if (split[2][i] < '0' || split[2][i] > '9')
			ft_exit("Invalid sprite frame per movement");
	}
	sprite->frame_per_movement = ft_atoi(split[2]);
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
		if (line[i] == '1' || line[i] == '0' || line[i] == ' ')
			flag = SUCCESS;
		if (line[i] == 'D' || line[i] == 'Z' || line[i] == 'N'
			|| line[i] == 'S' || line[i] == 'W' || line[i] == 'E')
			flag = SUCCESS;
		if (flag == FAIL)
			ft_exit("Invalid map using not valid value");
	}
	return (SUCCESS);
}
