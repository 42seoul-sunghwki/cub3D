/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 22:35:17 by sunghwki          #+#    #+#             */
/*   Updated: 2024/04/05 15:06:22 by sunghwki         ###   ########.fr       */
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

typedef struct s_mlx		t_mlx;
typedef struct s_data		t_data;
typedef struct s_map		t_map;
typedef struct s_pic		t_pic;
typedef struct s_sprite		t_sprite;
typedef struct s_user		t_user;
typedef struct s_block		t_block;
typedef struct s_line_lst	t_line_lst;
typedef struct s_lst_head	t_lst_head;

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

typedef struct s_map {
	int		w;
	int		h;
	char	**map;
}	t_map;

typedef struct s_lst_head
{
	int			w;
	int			h;
	t_line_lst	*head;
	t_line_lst	*tail;
}	t_lst_head;

typedef struct s_line_lst
{
	int			size;
	char		*line;
	t_line_lst	*next;
}	t_line_lst;

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
}	t_user;

/**
 * 
*/
typedef struct s_mlx {
	void		*mlx;
	void		*win;
	t_data		img_data[2];
	int			num_frame;
	size_t		total_frame;
	size_t		start;
	t_map		*map;
	t_block		*block;
	t_sprite	*sprite;
	t_user		*user;
	t_pic		font[10];
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
t_line_lst		*init_line_lst(char *line);

/* free_struct.c */
void			free_line_lst(t_line_lst *lst);

/* cub_slice.c */
int				slice_cub(char *line, t_mlx *graphic, t_block *block);

/* cub_check.c */
int				check_img_cub(char **split, t_mlx *graphic, t_pic **org_img);

/* cub_read.c */
int				read_cub(char *cub, t_mlx *graphic);

/* cub_helper.c */
int				color_cub(char **split);

/* cub_list.c */
t_lst_head		*push_lst(t_lst_head *head, t_line_lst *new);
char			**lst_to_arr(t_lst_head *head);
t_line_lst		*init_line_lst(char *line);
t_lst_head		*init_lst_head(void);
void			free_lst_head(t_lst_head *head);

/* init_struct.c */
t_user			*init_user(void);

/* frame.c */
size_t			get_time_in_us(void);

/**
 * open_file.c
 * 
*/
int		open_file(char *file);
int		close_file(int fd);

#endif
