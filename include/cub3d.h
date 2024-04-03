/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 22:35:17 by sunghwki          #+#    #+#             */
/*   Updated: 2024/04/03 16:48:33 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WINWIDTH 1920
# define WINHEIGHT 1080

# define IMG_W		64
# define IMG_H		64

# define UNDEFINED	-1
# define SUCCESS	0
# define FAIL		1

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>

/*
* 이중 버퍼링
*/
typedef struct s_mlx {
	void	*mlx;
	void	*win;
	t_data	data[2];
}	t_mlx;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_map {
	int		w;
	int		h;
	char	**map;
}	t_map;

/**
* 이미지 저장
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

typedef struct s_block {
	t_pic	*no;
	t_pic	*so;
	t_pic	*we;
	t_pic	*ea;
	t_pic	*fi;
	t_pic	*ci;
	int		f_trgb;
	int		c_trgb;
}	t_block;

typedef struct s_user {
	double	x;
	double	y;
	double	z;
	int		map_x;
	int		map_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	old_time;
	double	new_time;
}	t_user;

/**
 * open_file.c
 * 
*/
int		open_file(char *file);
int		close_file(int fd);

/**
 * free_pointer.c
*/
void	free_2d_ptr(char **ptr);
#endif
