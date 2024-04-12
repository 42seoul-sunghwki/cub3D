/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 22:28:56 by minsepar          #+#    #+#             */
/*   Updated: 2024/04/12 20:36:42 by minsepar         ###   ########.fr       */
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
		graphic->img_data[i].img = mlx_new_image(graphic->mlx, WINWIDTH, WINHEIGHT);
		get_img_addr(&graphic->img_data[i]);
		printf("%d\n", graphic->img_data[i].endian);
		ft_memset(graphic->img_data[i].addr, 0, sizeof(int) * (WINWIDTH * WINHEIGHT));
	}
	init_user(&graphic->user);
	graphic->dda.cos_rot_speed = cos(graphic->user.rot_speed);
	graphic->dda.sin_rot_speed = sin(graphic->user.rot_speed);
	graphic->num_frame = 0;
	graphic->total_frame = 0;
	graphic->block.f_trgb = 0xced4da;
	graphic->block.c_trgb = 0;
}

int	main(int argc, char **argv)
{
	t_mlx	graphic;
	t_map	*map;
	(void) argc;
	(void) argv;

	map = &graphic.map;
	map->w = 10;
	map->h = 10;
	map->map = malloc(sizeof(char *) * 21);
	map->map[0] = "1111111111";
	map->map[1] = "1000000001";
	map->map[2] = "3000000004";
	map->map[3] = "2000000001";
	map->map[4] = "1000010002";
	map->map[5] = "4000000003";
	map->map[6] = "3000000004";
	map->map[7] = "2000000001";
	map->map[8] = "1000000002";
	map->map[9] = "1000000002";
	map->map[10] = "1000000002";
	map->map[11] = "1000000002";
	map->map[12] = "1000000002";
	map->map[13] = "1000000002";
	map->map[14] = "1000000002";
	map->map[15] = "1000000002";
	map->map[16] = "1000000002";
	map->map[17] = "1000000002";
	map->map[18] = "1000000002";
	map->map[19] = "1000000002";
	map->map[20] = "1111111111";
	init_t_mlx(&graphic);
	init_block_temp(&graphic);
	mlx_hook(graphic.win, 17, 0L, terminate_program, &graphic);
	mlx_loop_hook(graphic.mlx, game_loop, &graphic);
	mlx_hook(graphic.win, 02, 1L, handle_keypress, &graphic);
	mlx_mouse_hook(graphic.win, handle_mouse, &graphic);
	mlx_loop(graphic.mlx);
}
