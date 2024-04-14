/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 20:24:29 by sunghwki          #+#    #+#             */
/*   Updated: 2024/04/14 20:38:01 by sunghwki         ###   ########.fr       */
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
		ft_memset(graphic->img_data[i].addr, 0, sizeof(int) * (WINWIDTH * WINHEIGHT));
	}
	graphic->num_frame = 0;
	graphic->total_frame = 0;
	graphic->block.f_trgb = 0xced4da;
	graphic->block.c_trgb = 0;
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

int	main(int argc, char **argv)
{
	t_mlx	graphic;
	t_map	*map;
	t_sprite	*sprite;
	int		i;
	int		j;

	if (init_main(argc) == FAIL)
		return (1);
	ft_memset(&graphic, 0, sizeof(t_mlx));
	map = &graphic.map;
	init_t_mlx(&graphic);
	cub_to_struct(argv[1], &graphic);
	sprite = &(graphic.sprite[ZOMBIE]);
	i = -1;
	while (++i < sprite->img[0].w)
	{
		j = -1;
		while (++j < sprite->img[0].h)
		{
			printf("i: %d, j: %d\n", i, j);
			printf("sprite->img[0].data.addr[j * sprite->img[0].w + i]: %d\n", sprite->img[0].data.addr[j * sprite->img[0].w + i]);
			my_mlx_pixel_put(graphic.img_data[0].img, i, j, sprite->img[0].data.addr[j * sprite->img[0].w + i]);
		}
	}
	mlx_put_image_to_window(graphic.mlx, graphic.win, graphic.img_data[0].img, 0, 0);
	mlx_loop(graphic.mlx);
}
