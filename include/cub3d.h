/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 22:35:17 by sunghwki          #+#    #+#             */
/*   Updated: 2024/04/03 16:07:03 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include "mlx.h"

# define WINWIDTH 1920
# define WINHEIGHT 1080

typedef struct s_mlx	t_mlx;
typedef struct s_data	t_data;
typedef struct s_map	t_map;
typedef struct s_pic	t_pic;
typedef struct s_sprite	t_sprite;
typedef struct s_user	t_user;

/*
* double buffering
*/
typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_mlx {
	void	*mlx;
	void	*win;
	t_data	img_data[2];
}	t_mlx;

typedef struct s_map {
	int	w;
	int	h;
	int	map_x;
	int	map_y;
}	t_map;

/**
* image data
*/
typedef struct s_pic {
	int		w;
	int		h;
	void	*img;
}	t_pic;

typedef struct s_sprite {
	int		l;
	t_pic	*size;
}	t_sprite;

typedef struct s_user {
	double	x;
	double	y;
	double	z;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	old_time;
	double	new_time;
}	t_user;

/* mlx_hooks.c */
int	terminate_program(t_mlx *graphic);
int	key_down(int keypress, void *param);

#endif
