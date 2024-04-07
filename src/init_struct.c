/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:53:47 by sunghwki          #+#    #+#             */
/*   Updated: 2024/04/07 21:13:17 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// t_block	*init_block(void)
// {
// 	t_block	*block;

// 	block = (t_block *)malloc(sizeof(t_block));
// 	if (!block)
// 		return (NULL);
// 	block->no = NULL;
// 	block->so = NULL;
// 	block->we = NULL;
// 	block->ea = NULL;
// 	block->fi = NULL;
// 	block->ci = NULL;
// 	block->f_trgb = UNDEFINED;
// 	block->c_trgb = UNDEFINED;
// 	return (block);
// }

// t_pic	*init_pic(void)
// {
// 	t_pic	*pic;

// 	pic = (t_pic *)malloc(sizeof(t_pic));
// 	if (!pic)
// 		return (NULL);
// 	pic->w = IMG_W;
// 	pic->h = IMG_H;
// 	pic->img = NULL;
// 	return (pic);
// }

void	init_user(t_user *user)
{
	user->x = 5.0;
	user->y = 5.0;
	user->z = 48.0;
	user->map_x = 0;
	user->map_y = 0;
	user->dir_x = 1.0;
	user->dir_y = 1.0;
	user->plane_x = 1.0;
	user->plane_y = -1.0;
	user->move_speed = 0.05;
	user->rot_speed = 0.02;
}

void	get_img_addr(t_data *data)
{
	data->addr = mlx_get_data_addr(
			data->img,
			&data->bits_per_pixel,
			&data->line_length,
			&data->endian
			);
}

void	init_block_temp(t_mlx *graphic)
{
	t_pic	*pic;
	t_data	*data;
	char	*str;
	int		i;
	t_block	*block;

	block = &graphic->block;
	str = "./src/xpm_images/ender_block.xpm";
	i = -1;
	while (++i < 4)
	{
		pic = &block->pic[i];
		data = &pic->data;
		data->img = mlx_xpm_file_to_image(graphic, str, &pic->w, &pic->h);
		get_img_addr(data);
	}
}
