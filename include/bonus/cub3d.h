/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 22:35:17 by sunghwki          #+#    #+#             */
/*   Updated: 2024/04/16 16:01:56 by minsepar         ###   ########.fr       */
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

# define UNDEFINED	-1
# define SUCCESS	0
# define FAIL		1
# define WALL_RATIO 1.34

# define NO			0
# define SO			1
# define EA			2
# define WE			3
# define CI			4
# define FI			5

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

# define NUM_SPRITE	1
# define NUM_SPRITE_TYPE	4

/* user */
# define MOVE_SPEED	0.2
# define ROT_SPEED	0.05

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

typedef struct s_sprite_node
{
	float	x;
	float	y;
	int		sprite_type;
	float	distance;
	size_t	start_frame;
}	t_sprite_node;

typedef struct s_sprite_vec
{
	int	size;
	int	malloc_size;
	t_sprite_node	**list;
}	t_sprite_vec;

/**
 * 
*/
typedef struct s_sprite {
	int		num_img;
	t_pic	*img;
	size_t	frame_per_movement;
}	t_sprite;

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

typedef struct s_sprite_info
{
	float	sprite_x;
	float	sprite_y;
	float	inv_det;
	float	transform_x;
	float	transform_y;
	int		sprite_screen_x;
	int		sprite_height;
	int		draw_start_y;
	int		draw_end_y;
	int		sprite_width;
	int		draw_start_x;
	int		draw_end_x;
	int		tex_x;
	int		tex_y;
}	t_sprite_info;

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
	void			*mlx;
	void			*win;
	t_data			img_data[2];
	int				num_frame;
	size_t			total_frame;
	t_map			map;
	t_block			block;
	t_sprite		sprite[NUM_SPRITE];
	t_sprite_vec	sprite_vec;
	t_sprite_info	sprite_info;
	t_user			user;
	size_t			time;
	t_dda			dda;
}	t_mlx;

//tmp
void			print_map(t_map *map);

/* mlx_hooks_bonus.c */
int				terminate_program(t_mlx *graphic);

/* mlx_pixel_bonus.c */
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
int				my_mlx_pixel_get(t_data *data, int x, int y);
int				blend_trgb(int fg_color, int bg_color);
void			draw_vertical_line(t_mlx *mlx, t_dda *dda);

/* mlx_color_bonus.c */
int				create_trgb(unsigned char t, unsigned char r,
					unsigned char g, unsigned char b);
unsigned char	get_t(int trgb);
unsigned char	get_r(int trgb);
unsigned char	get_g(int trgb);
unsigned char	get_b(int trgb);

/* open_file_bonus.c */
int				open_file(char *file);
int				close_file(int fd);

/* free_pointer_bonus.c */
void			free_2d_ptr(char **ptr);

/* init_struct_bonus.c */
void			init_block(t_block *block);
void			init_pic(t_pic *pic);
void			init_user(t_user *user, int x, int y, char pos);
t_line_lst		*init_line_lst(char *line);

/* free_struct_bonus.c */
void			free_line_lst(t_line_lst *lst);

/* ft_lib_bonus.c */
int				ft_sanitize_enter(char *line);

/* cub_to_struct_bonus.c */
int				cub_to_struct(char *file, t_mlx *mlx);

/* cub_slice_bonus.c */
int				slice_cub(char *line, t_mlx *graphic, t_block *block);

/* cub_check_bonus.c */
int				check_img_cub(char **split, t_mlx *graphic, t_pic *org_img);

/* cub_read_bonus.c */
char			*read_cub(int fd, t_mlx *graphic);

/* cub_dup_valid_bonus.c */
void			cub_dup_valid(t_mlx *mlx);

/* cub_helper_bonus.c */
int				color_cub(char **split);

/* cub_map_bonus.c */
int				map_cub(char *line, int fd, t_map *map);
int				check_map_cub(char *line);

/* cub_list_bonus.c */
t_lst_head		*push_lst(t_lst_head *head, t_line_lst *new);
char			**lst_to_arr(t_lst_head *head);
t_line_lst		*init_line_lst(char *line);
t_lst_head		*init_lst_head(void);
void			free_lst(t_lst_head *head);

/* cub_map_valid_bonus.c */
int				cub_map_valid(t_map *map);

/* init_struct_bonus.c */
void			get_img_addr(t_data *data);

/* frame_bonus.c */
void			display_frame(t_mlx *graphic);

/* game_loop_bonus.c */
int				game_loop(void *arg);

/* init_dda_data_bonus.c */
void			init_data(t_dda *dda, t_user *user, int x_pixel_num);

/* handle_keypress_bonus.c */
int				handle_keypress(int keycode, void *arg);
size_t			get_time_in_us(void);

/* handle_mouse_bonus.c */
int				handle_mouse(int button, int x, int y, void *arg);

/* collision_check_bonus.c */
void			dir_y_check_p(t_map *map,
					t_user *user, float new_displacement_y);
void			dir_y_check_n(t_map *map,
					t_user *user, float new_displacement_y);
void			dir_x_check_p(t_map *map,
					t_user *user, float new_displacement_x);
void			dir_x_check_n(t_map *map,
					t_user *user, float new_displacement_x);

/* draw_sprite_bonus.c */
void			update_sprite(t_mlx *graphic, t_user *user);

/* mergesort_sprite_bonus.c */
t_sprite_node	**mergesort_sprite_list(t_sprite_node **list, int size);

/* handle_arrow_bonus.c */
void			handle_left_arrow(t_mlx *graphic, int keycode);
void			handle_right_arrow(t_mlx *graphic, int keycode);
void			check_collision(t_mlx *graphic, int keycode);

/* sprite_list_bonus.c */
void			init_sprite_vec(t_sprite_vec *vec);
void			push_sprite(t_sprite_vec *vec, t_sprite_node *node);
t_sprite_node	*get_sprite(t_sprite_vec *vec, int index);
void			delete_sprite(t_sprite_vec *vec, int index);
t_sprite_node	*create_sprite_node(float x, float y,
					int sprite_type);

/**
 * open_file.c
 * 
*/
int		open_file(char *file);
int		close_file(int fd);

#endif
