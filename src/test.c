/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:25:04 by sunghwki          #+#    #+#             */
/*   Updated: 2024/04/12 18:35:52 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int argc, char *argv[])
{
	
	t_mlx graphic;
	graphic.mlx = mlx_init();
	graphic.win = mlx_new_window(graphic.mlx, WINWIDTH, WINHEIGHT, "cub3D");
	int i = -1;
	while (++i < 2)
	{
		graphic.img_data[i].img = mlx_new_image(graphic.mlx, WINWIDTH, WINHEIGHT);
		get_img_addr(&graphic.img_data[i]);
		printf("%d\n", graphic.img_data[i].endian);
		ft_memset(graphic.img_data[i].addr, 0, sizeof(int) * (WINWIDTH * WINHEIGHT));
	}
	cub_to_struct(argv[1], &graphic);
	mlx_put_image_to_window(graphic.mlx, graphic.win, graphic.block.pic[0].data.img, 0, 0);
	mlx_put_image_to_window(graphic.mlx, graphic.win, graphic.block.pic[1].data.img, 0, 160);
	mlx_put_image_to_window(graphic.mlx, graphic.win, graphic.block.pic[2].data.img, 0, 320);
	mlx_put_image_to_window(graphic.mlx, graphic.win, graphic.block.pic[3].data.img, 0, 480);
	mlx_loop(graphic.mlx);
}
