/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 22:28:56 by minsepar          #+#    #+#             */
/*   Updated: 2024/04/07 20:45:15 by sunghwki         ###   ########.fr       */
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
	init_block(&(graphic->block));
	init_user(&graphic->user);
	graphic->num_frame = 0;
	graphic->total_frame = 0;
}

int	init_main(int argc)
{
	if (argc != 2)
	{
		perror("Error\nInvalid number of arguments");
		return (FAIL);
	}
	else
	{
		return (SUCCESS);
	}
}

void	print_map(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->h)
	{
		printf("%s\n", map->map[i]);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_mlx	graphic;
	t_map	*map;

	if (init_main(argc) == FAIL)
		return (1);
	map = &graphic.map;
	//map->w = 10;
	//map->h = 10;
	//map->map = malloc(sizeof(char *) * 10);
	//map->map[0] = "1234123412";
	//map->map[1] = "4000000003";
	//map->map[2] = "3000011004";
	//map->map[3] = "2000000001";
	//map->map[4] = "1000000002";
	//map->map[5] = "4000000003";
	//map->map[6] = "3000000004";
	//map->map[7] = "2001000001";
	//map->map[8] = "1000000002";
	//map->map[9] = "4321432143";

	if (read_cub(argv[1], &graphic))
	{
		perror("Error\n"); //tmp
		return (1);
	}
	print_map(map);
	init_t_mlx(&graphic);
	mlx_hook(graphic.win, 17, 0L, terminate_program, &graphic);
	mlx_hook(graphic.win, 02, 0L, key_down, &graphic);
	// for (int i = 0; i < 50; i++)
	// {
	// 	for (int j = 0; j < 1080; j++)
	// 	{
	// 		my_mlx_pixel_put(&graphic.img_data[graphic.num_frame], i, j, RED);
	// 	}
	// }
	// int color;
	// for (int i = 0; i < 200; i++)
	// {
	// 	for (int j = 0; j < 100; j++)
	// 	{
	// 		color = blend_trgb(0xB000FF00,
	// 			my_mlx_pixel_get(&graphic.img_data[graphic.num_frame], i, j));
	// 		my_mlx_pixel_put(&graphic.img_data[graphic.num_frame], i, j, color);
			
	// 	}
	// }
	// mlx_put_image_to_window(graphic.mlx, graphic.win,
	// 	graphic.img_data[graphic.num_frame].img, 0, 0);
	// t_pic	font;
	// t_data	font_img;

	// char	*file_dir = "./src/font/1.xpm";

	// font_img.img = mlx_xpm_file_to_image(graphic.mlx, file_dir, &font.w, &font.h);
	// font_img.addr = mlx_get_data_addr(
	// 	font_img.img,
	// 	&font_img.bits_per_pixel,
	// 	&font_img.line_length,
	// 	&font_img.endian
	// 	);
	// mlx_put_image_to_window(graphic.mlx, graphic.win,
	// 	font_img.img, 500, 500);
	// mlx_string_put(graphic.mlx, graphic.win, 20, 20, 0xFF00, "60");
	mlx_loop_hook(graphic.mlx, game_loop, &graphic);
	mlx_hook(graphic.win, 02, 0L, handle_keypress, &graphic);
	mlx_loop(graphic.mlx);
}
