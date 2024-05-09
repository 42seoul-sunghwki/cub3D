/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 22:28:56 by minsepar          #+#    #+#             */
/*   Updated: 2024/05/09 13:52:57 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_t_mlx(t_mlx *graphic)
{
	int	i;

	i = -1;
	graphic->mlx = mlx_init();
	graphic->win = mlx_new_window(graphic->mlx, WINWIDTH, WINHEIGHT, "cub3D");
	while (++i < 2)
	{
		graphic->img_data[i].img = mlx_new_image(graphic->mlx,
				WINWIDTH, WINHEIGHT);
		get_img_addr(&graphic->img_data[i]);
		ft_memset(graphic->img_data[i].addr, 0,
			sizeof(int) * (WINWIDTH * WINHEIGHT));
	}
	graphic->num_frame = 0;
	graphic->total_frame = 0;
	graphic->block.f_trgb = -1;
	graphic->block.c_trgb = -1;
}

int	init_main(int argc)
{
	if (argc != 2)
	{
		printf("Error\nInvalid number of arguments");
		return (FAIL);
	}
	else
		return (SUCCESS);
}

void	leaks_check()
{
	system("leaks cub3D");
}

int	main(int argc, char **argv)
{
	t_mlx	graphic;

	atexit(leaks_check);
	if (init_main(argc) == FAIL)
		return (1);
	ft_memset(&graphic, 0, sizeof(t_mlx));
	init_t_mlx(&graphic);
	cub_to_struct(argv[1], &graphic);
	mlx_loop_hook(graphic.mlx, game_loop, &graphic);
	mlx_hook(graphic.win, 02, 1L, handle_keypress, &graphic);
	mlx_hook(graphic.win, 17, 0, terminate_program, &graphic);
	mlx_loop(graphic.mlx);
}
