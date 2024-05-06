/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 19:10:42 by minsepar          #+#    #+#             */
/*   Updated: 2024/05/06 21:25:48 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	init_t_mlx_helper(t_mlx *graphic, char **argv)
{
	t_sprite_vec	*vec;

	graphic->weapon_num = 0;
	graphic->pepsi_open = false;
	graphic->change_weapon_num = 1;
	graphic->weapon_sprite[1] = PEPSI_DRAW;
	graphic->weapon_start_frame = 0;
	vec = &graphic->sprite_vec;
	init_minimap(&graphic->minimap);
	init_sprite_vec(vec);
	cub_to_struct(argv[1], graphic);
	parse_door_map(graphic);
	graphic->num_threads = sysconf(_SC_NPROCESSORS_ONLN);
	if (graphic->num_threads < 0)
		perror("sysconf");
	thread_pool_init(&graphic->pool, graphic->num_threads);
	init_frame_thread(graphic);
}

void	init_t_mlx(t_mlx *graphic, char **argv)
{
	int			i;

	i = -1;
	graphic->mlx = mlx_init();
	graphic->win = mlx_new_window(graphic->mlx, WINWIDTH, WINHEIGHT, "cub3D");
	ft_memset(graphic->key_states, 0, sizeof(bool) * UINT16_MAX);
	while (++i < 3)
	{
		graphic->img_data[i].img
			= mlx_new_image(graphic->mlx, WINWIDTH, WINHEIGHT);
		get_img_addr(&graphic->img_data[i]);
		ft_memset(graphic->img_data[i].addr, 0,
			sizeof(int) * (WINWIDTH * WINHEIGHT));
	}
	init_sprite_fpm(graphic);
	graphic->num_frame = 0;
	graphic->num_frame_render = 0;
	graphic->total_frame = 0;
	graphic->block.f_trgb = 0xced4da;
	graphic->block.c_trgb = 0;
	init_t_mlx_helper(graphic, argv);
}
