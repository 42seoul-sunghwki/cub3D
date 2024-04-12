/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:53:47 by sunghwki          #+#    #+#             */
/*   Updated: 2024/04/12 20:51:43 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_block(t_block *block)
{
	int		i;

	i = -1;
	while (++i < 6)
	{
		init_pic(&(block->pic[i]));
	}
	block->f_trgb = UNDEFINED;
	block->c_trgb = UNDEFINED;
}

void	init_t_data(t_data *data)
{
	data->img = NULL;
	data->addr = NULL;
	data->bits_per_pixel = 0;
	data->line_length = 0;
	data->endian = 0;
}

void	init_pic(t_pic *pic)
{
	pic->w = IMG_W;
	pic->h = IMG_H;
	init_t_data(&(pic->data));
}

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


void	init_user(t_user *user, int x, int y, char pos)
{
	user->x = (double)x;
	user->y = (double)y;
	user->z = 48.0;
	user->map_x = 0;
	user->map_y = 0;
	user->dir_x = 0.0;
	user->dir_y = 0.0;
	user->plane_x = 0.0;
	user->plane_y = 0.0;
	if (pos == 'N')
	{
		user->dir_y = 1.0;
		user->plane_x = 0.66;
	}
	else if (pos == 'S')
	{
		user->dir_y = -1.0;
		user->plane_x = -0.66;
	}
	else if (pos == 'W')
	{
		user->dir_x = -1.0;
		user->plane_y = 0.66;
	}
	else if (pos == 'E')
	{
		user->dir_x = 1.0;
		user->plane_y = -0.66;
	}
	user->move_speed = 0.5;
	user->rot_speed = 0.8;
}

void	get_img_addr(t_data *data)
{
	data->addr = mlx_get_data_addr(
			data->img,
			&data->bits_per_pixel,
			&data->line_length,
			&data->endian
			);
	printf("data->addr: [%p]\n", data->addr);
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
	// pic = &block->pic[i];
	// data = &pic->data;
	// data->img = mlx_xpm_file_to_image(graphic, str, &pic->w, &pic->h);
	// get_img_addr(data);
	while (++i < 4)
	{
		pic = &block->pic[i];
		data = &pic->data;
		data->img = mlx_xpm_file_to_image(graphic->mlx, str, &pic->w, &pic->h);
		get_img_addr(data);
		printf("init_block data->img [%p]\n", data->img);
	}
	str = "./src/xpm_images/stone.xpm";
	i--;
	while (++i < 6)
	{
		pic = &block->pic[i];
		data = &pic->data;
		data->img = mlx_xpm_file_to_image(graphic->mlx, str, &pic->w, &pic->h);
		printf("data->img %p\n", data->img);
		get_img_addr(data);
		printf("init_block data->img [%p]\n", data->img);
	}
}
