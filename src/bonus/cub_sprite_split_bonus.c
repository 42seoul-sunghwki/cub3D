/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_sprite_split_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 18:36:47 by sunghwki          #+#    #+#             */
/*   Updated: 2024/04/24 13:33:52 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	cub_sprite_init_bonus(t_sprite *sprite, t_pic *tmp)
{
	int	i;

	sprite->img = (t_pic *)malloc(sizeof(t_pic) * sprite->num_img);
	if (sprite->img == NULL)
		ft_exit("Malloc failed");
	i = -1;
	while (++i < sprite->num_img)
	{
		sprite->img[i].w = tmp->w / sprite->num_img;
		sprite->img[i].h = tmp->h;
		sprite->img[i].data.img = tmp->data.img;
		sprite->img[i].data.addr = (char *)malloc(sizeof(char)
				* sprite->img[i].w * sprite->img[i].h * 4
				/ sprite->num_img + 1);
		sprite->img[i].data.addr[sprite->img[i].w
			* sprite->img[i].h * 4] = '\0';
		sprite->img[i].data.bits_per_pixel = tmp->data.bits_per_pixel;
		sprite->img[i].data.line_length = tmp->data.line_length
			/ sprite->num_img;
		sprite->img[i].data.endian = tmp->data.endian;
	}
}

int	cub_sprite_bonus(t_sprite *sprite)
{
	t_pic	*tmp;
	int		i;
	int		j;

	if (sprite->img->w <= 0 || sprite->img->h <= 0)
		ft_exit ("Not sprite size is too small");
	tmp = sprite->img;
	cub_sprite_init_bonus(sprite, tmp);
	i = -1;
	while (++i < sprite->num_img)
	{
		j = -1;
		while (++j < sprite->img[i].h)
		{
			ft_memmove(sprite->img[j].data.addr + tmp->w * 4 * i,
				tmp->data.addr + (tmp->w * 4 * i) * j, tmp->w * 4);
		}
	}
	free(tmp->data.addr);
	free(tmp);
	return (SUCCESS);
}
