/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 19:23:08 by sunghwki          #+#    #+#             */
/*   Updated: 2024/04/12 20:09:29 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_img_cub(char **split, t_mlx *graphic, t_pic **org_img)
{
	t_pic	*pic;

	if (split[0] == NULL || split[1] == NULL || split[2] != NULL)
	{
		printf("Error\nInvalid cub file");
		return (FAIL);
	}
	pic = init_pic();
	if (!pic)
		return (FAIL);
	*org_img = pic;
	(*org_img)->img = mlx_xpm_file_to_image(graphic->mlx, split[1],
			&(*org_img)->w, &(*org_img)->h);
	if (!(*org_img)->img)
	{
		free(pic);
		printf("Error\nInvalid cub file in img");
		return (FAIL);
	}
	return (SUCCESS);
}
