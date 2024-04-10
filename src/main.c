/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 22:28:56 by minsepar          #+#    #+#             */
/*   Updated: 2024/04/09 22:09:45 by sunghwki         ###   ########.fr       */
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
	//init_user(&graphic->user);
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

	init_t_mlx(&graphic);
	if (read_cub(argv[1], &graphic))
	{
		perror("Error\n");
		exit (1);
	}
	if (cub_valid(map) == FAIL)
	{
		perror("Error\nInvalid map");
		exit (1);
	}
	print_map(map);
	init_user(&graphic.user, 1, 1, 'N');
	mlx_hook(graphic.win, 17, 0L, terminate_program, &graphic);
	mlx_hook(graphic.win, 02, 0L, key_down, &graphic);
	mlx_loop_hook(graphic.mlx, game_loop, &graphic);
	mlx_hook(graphic.win, 02, 0L, handle_keypress, &graphic);
	mlx_loop(graphic.mlx);
}
