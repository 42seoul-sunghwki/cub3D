/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 22:35:17 by sunghwki          #+#    #+#             */
/*   Updated: 2024/04/03 21:18:23 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include "mlx.h"

# define WINWIDTH 1920
# define WINHEIGHT 1080

# define RED 0xFF << 16
# define GREEN 0xFF << 8
# define BLUE  0xFF

# define IMG_W		64
# define IMG_H		64

# define UNDEFINED	-1
# define SUCCESS	0
# define FAIL		1

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>

typedef struct s_mlx	t_mlx;
typedef struct s_data	t_data;
typedef struct s_map	t_map;
typedef struct s_pic	t_pic;
typedef struct s_sprite	t_sprite;
typedef struct s_user	t_user;
typedef struct s_block	t_block;

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
	int		num_frame;
}	t_mlx;

typedef struct s_map {
	int		w;
	int		h;
	char	**map;
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

/* mlx_hooks.c */
int				terminate_program(t_mlx *graphic);
int				key_down(int keypress, void *param);

/* mlx_pixel.c */
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
int				my_mlx_pixel_get(t_data *data, int x, int y);

/* mlx_color.c */
int				create_trgb(unsigned char t, unsigned char r,
					unsigned char g, unsigned char b);
unsigned char	get_t(int trgb);
unsigned char	get_r(int trgb);
unsigned char	get_g(int trgb);
unsigned char	get_b(int trgb);

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
