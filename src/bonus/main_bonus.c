/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 22:28:56 by minsepar          #+#    #+#             */
/*   Updated: 2024/05/13 15:13:01 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	init_main(int argc)
{
	if (argc != 2)
	{
		printf("Error\nInvalid number of arguments");
		return (FAIL);
	}
	else
	{
		return (SUCCESS);
	}
}

void	mlx_setup(t_mlx *graphic)
{
	mlx_mouse_hide(graphic->mlx);
	graphic->flag |= MOUSE_MOVE;
}

int	main(int argc, char **argv)
{
	t_mlx	graphic;

	if (init_main(argc) == FAIL)
		return (1);
	ft_memset(&graphic, 0, sizeof(t_mlx));
	init_t_mlx(&graphic, argv);
	mlx_setup(&graphic);
	mlx_loop_hook(graphic.mlx, game_loop, &graphic);
	mlx_hook(graphic.win, 2, 0, handle_keypress, &graphic);
	mlx_hook(graphic.win, 3, 0, handle_keyrelease, &graphic);
	mlx_hook(graphic.win, 17, 0, terminate_program, &graphic);
	mlx_hook(graphic.win, 6, 0, handle_mouse_move, &graphic);
	mlx_mouse_hook(graphic.win, handle_mouse_click, &graphic);
	set_bg_sound(&graphic);
	load_sound(&graphic);
	mlx_loop(graphic.mlx);
}
