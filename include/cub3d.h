/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 22:35:17 by sunghwki          #+#    #+#             */
/*   Updated: 2024/04/05 00:00:16 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdbool.h>
# include <math.h>

# include "mlx.h"
# include "../lib/libftprintf/ft_printf.h"

# define WINWIDTH 1920
# define WINHEIGHT 1080

# define RED 0x00FF0000
# define GREEN 0xFF << 8
# define BLUE  0xFF

# define IMG_W		64
# define IMG_H		64

# define UNDEFINED	-1
# define SUCCESS	0
# define FAIL		1

typedef struct s_mlx	t_mlx;
typedef struct s_data	t_data;
typedef struct s_map	t_map;
typedef struct s_pic	t_pic;
typedef struct s_sprite	t_sprite;
typedef struct s_user	t_user;
typedef struct s_block	t_block;

/**
 * @var	void	*img
 * @var	char	*addr			the address to the first pixel to the image
 * @var	int		bits_per_pixel	the number of bits per pixel
 * @var	int		line_length		the number of lines for the particular image
 * @var	int		endian			information on either it uses little endian 
 * 								or big endian
 * 
*/
typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

/**
 * @var	int		w		the width of the map (in number of blocks)
 * @var	int		h		the height of the map (in number of blocks)
 * @var	char	**map	actual char bytes representing each block of the map
 * 
*/
typedef struct s_map {
	int		w;
	int		h;
	char	**map;
}	t_map;

/**
 * @var	int		w		the width of the texture data
 * @var	int		h		the height of the texture data
 * @var	void	*img
 * 
*/
typedef struct s_pic {
	int		w;
	int		h;
	void	*img;
}	t_pic;

/**
 * 
*/
typedef struct s_sprite {
	int		l;
	t_pic	*size;
}	t_sprite;

/**
 * 
*/
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

/**
 * @var	double	x		x position of the user
 * @var	double	y		y position of the user
 * @var	double	z		z position of the user
 * @var	int		map_x	x position of the square the user is currently in
 * @var	int		map_y	y position of the square the user is currently in
 * @var	double	dir_x	x component of direction vector of the user
 * @var	double	dir_y	y component of direction vector of the user
 * @var	double	plane_x	x component of direction vector of the plane
 * @var	double	plane_y	y component of direction vector of the plane
*/
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
}	t_user;

/**
 * @var	double	camera_x		x-coordinate of the current ray in camera space.
 * 								Left most value is 1, middle is 0, right is 2
 * @var	double	raydir_x		x component of the ray direction vector
 * @var	double	raydir_y		y component of the ray direction vector
 * @var	double	side_dist_x		distance left until the block in the x direction
 * @var	double	side_dist_y		distance left until the block in the y direction
 * @var	double	delta_dist_x	unit distance towards next block in x direction
 * @var	double	delta_dist_y	unit distance towards next block in y direction
 * @var	double	perp_wall_dist	perpendicular distance from user's view plane 
 * 								to the object
 * @var	int		step_x			which direction to step in x direction, -1 or 1
 * @var	int		step_y			which direction to step in y direction, -1 or 1
 * @var	int		collision_flag	collision_flag of the ray
 * @var	int		side			indicator to which side of the wall was hit 
 * 								NS = 1 or EW = 0
*/
typedef struct s_dda {
	double	camera_x;
	double	raydir_x;
	double	raydir_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		collision_flag;
	int		side;
}	t_dda;

/**
 * t_mlx struct gets passed to the game_loop function which renders each frame
 * 
 * @var	void	*mlx
 * @var	void	*win
 * @var	t_data	img_data[2]	two img data struct used to double buffer
 * @var	int		num_frame	index of the img_data to render to screen
 * @var	size_t	total_frame	count of total_frame rendered
 * 
*/
typedef struct s_mlx {
	void		*mlx;
	void		*win;
	t_data		img_data[2];
	int			num_frame;
	size_t		total_frame;
	t_map		map;
	t_block		block;
	t_sprite	*sprite;
	t_user		user;
}	t_mlx;

/* mlx_hooks.c */
int				terminate_program(t_mlx *graphic);
int				key_down(int keypress, void *param);

/* mlx_pixel.c */
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
int				my_mlx_pixel_get(t_data *data, int x, int y);
int				blend_trgb(int fg_color, int bg_color);

/* mlx_color.c */
int				create_trgb(unsigned char t, unsigned char r,
					unsigned char g, unsigned char b);
unsigned char	get_t(int trgb);
unsigned char	get_r(int trgb);
unsigned char	get_g(int trgb);
unsigned char	get_b(int trgb);


/* open_file.c */
int				open_file(char *file);
int				close_file(int fd);

/* free_pointer.c */
void			free_2d_ptr(char **ptr);

/* init_struct.c */
t_block			*init_block(void);
t_pic			*init_pic(void);

/* cub_slice.c */
int				slice_cub(char *line, t_mlx *graphic, t_block *block);

/* cub_check.c */
int				check_img_cub(char **split, t_mlx *graphic, t_pic **org_img);

/* cub_read.c */
int				read_cub(char *cub, t_mlx *graphic, t_map *map, t_block *block);

/* cub_helper.c */
int				color_cub(char **split);

/* init_struct.c */
void			init_user(t_user *user);

/* frame.c */
size_t	get_time_in_us(void);

/**
 * open_file.c
 * 
*/
int		open_file(char *file);
int		close_file(int fd);

#endif
