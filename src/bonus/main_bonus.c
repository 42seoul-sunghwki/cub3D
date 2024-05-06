/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 22:28:56 by minsepar          #+#    #+#             */
/*   Updated: 2024/05/06 21:16:25 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	init_t_mlx(t_mlx *graphic, char **argv)
{
	int			i;
	//t_sprite	*sprite;

	i = -1;
	graphic->mlx = mlx_init();
	graphic->win = mlx_new_window(graphic->mlx, WINWIDTH, WINHEIGHT, "cub3D");
	ft_memset(graphic->key_states, 0, sizeof(bool) * UINT16_MAX);
	while (++i < 3)
	{
		graphic->img_data[i].img = mlx_new_image(graphic->mlx, WINWIDTH, WINHEIGHT);
		get_img_addr(&graphic->img_data[i]);
		ft_memset(graphic->img_data[i].addr, 0, sizeof(int) * (WINWIDTH * WINHEIGHT));
	}
	init_sprite_fpm(graphic);
	graphic->num_frame = 0;
	graphic->num_frame_render = 0;
	graphic->total_frame = 0;
	graphic->block.f_trgb = 0xced4da;
	graphic->block.c_trgb = 0;
	graphic->weapon_num = 0;
	graphic->pepsi_open = false;
	//weapon setting
	graphic->change_weapon_num = 1;
	graphic->weapon_sprite[1] = PEPSI_DRAW;
	graphic->weapon_start_frame = 0;
	t_sprite_vec	*vec = &graphic->sprite_vec;
	init_minimap(&graphic->minimap);
	init_sprite_vec(vec);
	cub_to_struct(argv[1], graphic);
	//push_sprite(vec, create_sprite_node(3, 4, DANCING_BEAR, 0)); //refine map
	//push_sprite(vec, create_sprite_node(3, 3, DANCING_DOG, 0));
	//push_sprite(vec, create_sprite_node(3, 4, DANCING_CAT, 0));
	/* door_array */
	parse_door_map(graphic);
	/* multi-thread */
	graphic->num_threads = sysconf(_SC_NPROCESSORS_ONLN);
	if (graphic->num_threads < 0)
		perror("sysconf");
	printf("num_threads: [%ld]\n", graphic->num_threads);
	thread_pool_init(&graphic->pool, graphic->num_threads);
	init_frame_thread(graphic);
}

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

void	print_struct(t_mlx *mlx)
{
	printf("mlx->map.w: %d\n", mlx->map.w);
	printf("mlx->map.h: %d\n", mlx->map.h);
	printf("mlx->user.x: %f\n", mlx->user.x);
	printf("mlx->user.y: %f\n", mlx->user.y);
	printf("mlx->user.rot_speed: %f\n", mlx->user.rot_speed);
	//print_map(&mlx->map);
}

// void	check()
// {
// 	system("leaks cub3D");
// }

void	mlx_setup(t_mlx *graphic)
{
	mlx_mouse_hide(graphic->mlx);
	mlx_mouse_move(graphic->win, HALF_WINWIDTH, HALF_WINHEIGHT);
}

// void	leaks()
// {
// 	system("leaks cub3D");
// }

int	main(int argc, char **argv)
{
	t_mlx	graphic;
	t_map	*map;
	// atexit(leaks);

	if (init_main(argc) == FAIL)
		return (1);
	ft_memset(&graphic, 0, sizeof(t_mlx));
	map = &graphic.map;
	init_t_mlx(&graphic, argv);
	//cub_to_struct(argv[1], &graphic);
	print_struct(&graphic);
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
