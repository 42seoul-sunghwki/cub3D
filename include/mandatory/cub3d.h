/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 22:35:17 by sunghwki          #+#    #+#             */
/*   Updated: 2024/04/13 17:28:39 by sunghwki         ###   ########.fr       */
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

# define WINWIDTH 1600
# define WINHEIGHT 900
# define HALF_WINHEIGHT 450

# define YELLOW 0xFFFF << 8
# define RED 0xFF << 16
# define GREEN 0xFF << 8
# define BLUE  0xFF

# define IMG_W	64
# define IMG_H	64

# define UNDEFINED	-1
# define SUCCESS	0
# define FAIL		1
# define WALL_RATIO 1.34

# define NORTH	0
# define SOUTH	1
# define EAST	2
# define WEST	3
# define SKY	4
# define FLOOR	5

# define INT_MAX	0x7FFFFFFF
# define INT_MIN	0x80000000

# define HITBOX			0.3
# define LEFT_ARROW		123
# define RIGHT_ARROW	124
# define DOWN_ARROW		125
# define UP_ARROW		126

# define ARROW_OFFSET	123

# define NUM_SPRITE_TYPE 1

typedef struct s_mlx		t_mlx;
typedef struct s_data		t_data;
typedef struct s_map		t_map;
typedef struct s_pic		t_pic;
typedef struct s_sprite		t_sprite;
typedef struct s_user		t_user;
typedef struct s_block		t_block;
typedef struct s_line_lst	t_line_lst;
typedef struct s_lst_head	t_lst_head;

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
 * @var	int		w		the width of the texture data
 * @var	int		h		the height of the texture data
 * @var	void	*img
 * 
*/
typedef struct s_pic {
	int		w;
	int		h;
	char	*name;
	t_data	data;
}	t_pic;

typedef struct s_floor {
	float	raydir_x_start;
	float	raydir_y_start;
	float	raydir_x_end;
	float	raydir_y_end;
	int		p;
	float	pos_z;
	float	row_distance;
	float	floor_step_x;
	float	floor_step_y;
	float	floor_x;
	float	floor_y;
	float	ty;
	float	tx;
	float	cell_x;
	float	cell_y;
}	t_floor;

/**
 * 
*/
typedef struct s_block {
	t_pic	pic[6];
	int		f_trgb;
	int		c_trgb;
}	t_block;

/**
 * @var	float	x			x position of the user
 * @var	float	y			y position of the user
 * @var	float	z			z position of the user
 * @var	int		map_x		x position of the square the user is currently in
 * @var	int		map_y		y position of the square the user is currently in
 * @var	float	dir_x		x component of direction vector of the user
 * @var	float	dir_y		y component of direction vector of the user
 * @var	float	plane_x		x component of direction vector of the plane
 * @var	float	plane_y		y component of direction vector of the plane
 * @var	float	move_speed	the move_speed of the user when up, down ey pressed
 * @var	float	rot_speed	the rotation speed of the user
*/
typedef struct s_user {
	float	x;
	float	y;
	float	z;
	int		map_x;
	int		map_y;
	float	dir_x;
	float	dir_y;
	float	plane_x;
	float	plane_y;
	float	move_speed;
	float	rot_speed;
}	t_user;

/**
 * @var	float	camera_x		x-coordinate of the current ray in camera space.
 * 								Left most value is 1, middle is 0, right is 2
 * @var	float	raydir_x		x component of the ray direction vector
 * @var	float	raydir_y		y component of the ray direction vector
 * @var	float	side_dist_x		distance left until the block in the x direction
 * @var	float	side_dist_y		distance left until the block in the y direction
 * @var	float	delta_dist_x	unit distance towards next block in x direction
 * @var	float	delta_dist_y	unit distance towards next block in y direction
 * @var	float	perp_wall_dist	perpendicular distance from user's view plane 
 * 								to the object
 * @var	int		step_x			which direction to step in x direction, -1 or 1
 * @var	int		step_y			which direction to step in y direction, -1 or 1
 * @var	int		collision_flag	collision_flag of the ray
 * @var	int		side			indicator to which side of the wall was hit 
 * 								NS = 1 or EW = 0
 * @var int		draw_start_y	the start y value of the vertical line drawing
 * @var int		draw_end_y		the end y value of the vertical line drawing
*/
typedef struct s_dda {
	float			camera_x;
	float			raydir_x;
	float			raydir_y;
	float			side_dist_x;
	float			side_dist_y;
	float			delta_dist_x;
	float			delta_dist_y;
	float			perp_wall_dist;
	float			wall_pixel_x;
	float			text_step;
	float			text_pos;
	float			line_height;
	float			cos_rot_speed;
	float			sin_rot_speed;
	float			z_buffer[WINWIDTH];
	int				draw_start_x;
	int				draw_end_x;
	int				step_x;
	int				step_y;
	int				collision_flag;
	int				side;
	int				draw_start_y;
	int				draw_end_y;
	int				cur_pixel_x;
	int				texture_num;
	int				texture_x;
}	t_dda;

/**
 * t_mlx struct gets passed to the game_loop function which renders each frame
 * 
 * @var	void	*mlx
 * @var	void	*win
 * @var	t_data	img_data[2]	two img data struct used to float buffer
 * @var	int		num_frame	index of the img_data to render to screen
 * @var	size_t	total_frame	count of total_frame rendered
 * @var	map
 * @var	block
 * @var	sprite
 * @var	user
 * @var	
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
	t_user		user;
	size_t		time;
	t_dda		dda;
}	t_mlx;

/* mlx_hooks.c */
int				terminate_program(t_mlx *graphic);

/* mlx_pixel.c */
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
int				my_mlx_pixel_get(t_data *data, int x, int y);
int				blend_trgb(int fg_color, int bg_color);
void			draw_vertical_line(t_mlx *mlx, t_dda *dda);

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
void			init_block(t_block *block);
void			init_pic(t_pic *pic);
void			init_user(t_user *user, float x, float y, char pos);
t_line_lst		*init_line_lst(char *line);

/* free_struct.c */
void			free_line_lst(t_line_lst *lst);

/* ft_lib.c */
int				ft_sanitize_enter(char *line);
void			ft_exit(char *str);

/* cub_to_struct.c */
/**
 * @brief	converts the cub file to the struct
*/
int				cub_to_struct(char *file, t_mlx *mlx);

/* cub_slice.c */
int				slice_cub(char *line, t_mlx *graphic, t_block *block);

/* cub_check.c */
int				check_img_cub(char **split, t_mlx *graphic, t_pic *org_img);

/* cub_read.c */
char			*read_cub(int fd, t_mlx *graphic);

/* cub_dup_valid.c */
void			cub_dup_valid(t_mlx *mlx);

/* cub_helper.c */
int				color_cub(char **split);

/* cub_map.c */
int				map_cub(char *line, int fd, t_map *map);
int				check_map_cub(char *line);

/* cub_list.c */
t_lst_head		*push_lst(t_lst_head *head, t_line_lst *new);
char			**lst_to_arr(t_lst_head *head);
t_line_lst		*init_line_lst(char *line);
t_lst_head		*init_lst_head(void);
void			free_lst(t_lst_head *head);

/* cub_map_valid.c */
int				cub_map_valid(t_map *map);

/* init_struct.c */
void			get_img_addr(t_data *data);

/* frame.c */
void			display_frame(t_mlx *graphic);

/* game_loop.c */
int				game_loop(void *arg);

/* init_dda_data.c */
void			init_data(t_dda *dda, t_user *user, int x_pixel_num);

/* handle_keypress.c */
int				handle_keypress(int keycode, void *arg);
size_t			get_time_in_us(void);

/* handle_mouse.c */
int				handle_mouse(int button, int x, int y, void *arg);

/* collision_check.c */
void			dir_y_check_p(t_map *map,
					t_user *user, float new_displacement_y);
void			dir_y_check_n(t_map *map,
					t_user *user, float new_displacement_y);
void			dir_x_check_p(t_map *map,
					t_user *user, float new_displacement_x);
void			dir_x_check_n(t_map *map,
					t_user *user, float new_displacement_x);

/**
 * open_file.c
*/
int				open_file(char *file);
int				close_file(int fd);

#endif
