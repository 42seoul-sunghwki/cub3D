/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 22:28:56 by minsepar          #+#    #+#             */
/*   Updated: 2024/04/21 19:03:00 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	init_t_mlx(t_mlx *graphic)
{
	int			i;
	t_sprite	*sprite;

	i = -1;
	graphic->mlx = mlx_init();
	graphic->win = mlx_new_window(graphic->mlx, WINWIDTH, WINHEIGHT, "cub3D");
	while (++i < 3)
	{
		graphic->img_data[i].img = mlx_new_image(graphic->mlx, WINWIDTH, WINHEIGHT);
		get_img_addr(&graphic->img_data[i]);
		ft_memset(graphic->img_data[i].addr, 0, sizeof(int) * (WINWIDTH * WINHEIGHT));
	}
	graphic->num_frame = 0;
	graphic->num_frame_render = 0;
	graphic->total_frame = 0;
	graphic->block.f_trgb = 0xced4da;
	graphic->block.c_trgb = 0;
	sprite = &graphic->sprite[0];
	sprite->num_img = 15;
	sprite->img = malloc(sizeof(t_pic) * 15);
	sprite->img[0].name = "./texture/zombie/male_xpm/Idle_1.xpm";
	sprite->img[1].name = "./texture/zombie/male_xpm/Idle_2.xpm";
	sprite->img[2].name = "./texture/zombie/male_xpm/Idle_3.xpm";
	sprite->img[3].name = "./texture/zombie/male_xpm/Idle_4.xpm";
	sprite->img[4].name = "./texture/zombie/male_xpm/Idle_5.xpm";
	sprite->img[5].name = "./texture/zombie/male_xpm/Idle_6.xpm";
	sprite->img[6].name = "./texture/zombie/male_xpm/Idle_7.xpm";
	sprite->img[7].name = "./texture/zombie/male_xpm/Idle_8.xpm";
	sprite->img[8].name = "./texture/zombie/male_xpm/Idle_9.xpm";
	sprite->img[9].name = "./texture/zombie/male_xpm/Idle_10.xpm";
	sprite->img[10].name = "./texture/zombie/male_xpm/Idle_11.xpm";
	sprite->img[11].name = "./texture/zombie/male_xpm/Idle_12.xpm";
	sprite->img[12].name = "./texture/zombie/male_xpm/Idle_13.xpm";
	sprite->img[13].name = "./texture/zombie/male_xpm/Idle_14.xpm";
	sprite->img[14].name = "./texture/zombie/male_xpm/Idle_15.xpm";
	i = -1;
	while (++i < 15)
	{
		sprite->img[i].data.img = mlx_xpm_file_to_image(graphic->mlx,
			sprite->img[i].name, &sprite->img[i].w, &sprite->img[i].h);
		get_img_addr(&sprite->img[i].data);
	}
	sprite->fpm = 4;
	t_sprite_vec	*vec = &graphic->sprite_vec;
	init_sprite_vec(vec);
	push_sprite(vec, create_sprite_node(2, 2, 0));
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
//tmp
void	print_map(t_map *map)
{
	int	i;

	i = 0;
	printf("map width: %d\n", map->w);
	printf("map height: %d\n", map->h);
	while (i < map->h)
	{
		printf("%s\n", map->map[i]);
		i++;
	}
}

void	print_struct(t_mlx *mlx)
{
	printf("mlx->map.w: %d\n", mlx->map.w);
	printf("mlx->map.h: %d\n", mlx->map.h);
	printf("mlx->user.x: %f\n", mlx->user.x);
	printf("mlx->user.y: %f\n", mlx->user.y);
	printf("mlx->user.rot_speed: %f\n", mlx->user.rot_speed);
	print_map(&mlx->map);
}

// void	check()
// {
// 	system("leaks cub3D");
// }

void	mlx_setup(t_mlx *graphic)
{
	//Mac
	mlx_mouse_hide(graphic->mlx);
	mlx_mouse_move(graphic->win, HALF_WINWIDTH, HALF_WINHEIGHT);
	//linux
	// mlx_mouse_hide(graphic->mlx, graphic->win);
	// mlx_mouse_move(graphic->mlx, graphic->win, HALF_WINWIDTH, HALF_WINHEIGHT);
}

int	main(int argc, char **argv)
{
	// atexit(check);
	t_mlx	graphic;
	t_map	*map;

	// (void) map;
	if (init_main(argc) == FAIL)
		return (1);
	ft_memset(&graphic, 0, sizeof(t_mlx));
	map = &graphic.map;
	init_t_mlx(&graphic);
	cub_to_struct(argv[1], &graphic);
	print_struct(&graphic);
	mlx_setup(&graphic);
	mlx_loop_hook(graphic.mlx, game_loop, &graphic);
	mlx_hook(graphic.win, 2, 1L, handle_keypress, &graphic);
	mlx_hook(graphic.win, 17, 1L << 17, terminate_program, &graphic);
	mlx_hook(graphic.win, 6, 1L << 6, handle_mouse_move, &graphic);
	mlx_mouse_hook(graphic.win, handle_mouse_click, &graphic);
	mlx_loop(graphic.mlx);
}
