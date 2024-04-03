/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 22:28:56 by minsepar          #+#    #+#             */
/*   Updated: 2024/04/03 22:03:40 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_t_mlx(t_mlx *graphic)
{
	int	i;

	i = -1;
	graphic->mlx = mlx_init();
	graphic->win = mlx_new_window(graphic->mlx, 1920, 1080, "cub3D");
	while (++i < 2)
	{
		graphic->img_data[i].img = mlx_new_image(graphic->mlx, 1920, 1080);
		graphic->img_data[i].addr = mlx_get_data_addr(
				graphic->img_data[i].img,
				&graphic->img_data[i].bits_per_pixel,
				&graphic->img_data[i].line_length,
				&graphic->img_data[i].endian);
	}
	graphic->num_frame = 0;
}

int	test_loop(void *arg)
{
	t_data *data_from;
	t_data *data_to;
	int		color;
	t_mlx	*graphic;

	graphic = arg;
	printf("%d\n", graphic->num_frame);
	data_from = &graphic->img_data[graphic->num_frame];
	data_to = &graphic->img_data[graphic->num_frame ^ 1];
	for (int i = 0; i < 1080; i++)
	{
		for (int j = 0; j < 1920; j++)
		{
			color = my_mlx_pixel_get(data_from, j, i);
			my_mlx_pixel_put(data_to, (j + 50) % 1920, i, color);
			// printf("color: %X\n", color);
			// printf("x: %d y: %d\n", j, i);
			// sleep(1);
		}
	}
	usleep(100000);
	mlx_put_image_to_window(graphic->mlx, graphic->win, data_to->img, 0, 0);
	graphic->num_frame ^= 1;
	return (1);
}

int	main(int argc, char **argv)
{
	t_mlx	graphic;
	t_map	map;

	map.w = 10;
	map.h = 10;
	map.map = malloc(sizeof(char *) * 10);
	map.map[0] = "1111111111";
	map.map[1] = "1000000001";
	map.map[2] = "1000000001";
	map.map[3] = "1000000001";
	map.map[4] = "1000000001";
	map.map[5] = "1000000001";
	map.map[6] = "1000000001";
	map.map[7] = "1000000001";
	map.map[8] = "1000000001";
	map.map[9] = "1111111111";
	init_t_mlx(&graphic);
	mlx_hook(graphic.win, 17, 0L, terminate_program, &graphic);
	mlx_hook(graphic.win, 02, 0L, key_down, &graphic);
	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 1080; j++)
		{
			my_mlx_pixel_put(&graphic.img_data[graphic.num_frame], i, j, RED);
		}
	}
	mlx_put_image_to_window(graphic.mlx, graphic.win,
		graphic.img_data[graphic.num_frame].img, 0, 0);
	mlx_loop_hook(graphic.mlx, test_loop, (void *)&graphic);
	mlx_loop(graphic.mlx);
}
