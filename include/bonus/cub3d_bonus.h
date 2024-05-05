/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 22:35:17 by sunghwki          #+#    #+#             */
/*   Updated: 2024/05/05 21:33:01 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdbool.h>
# include <math.h>
# include <pthread.h>
# include <dirent.h>
# include <string.h>

# include "mlx.h"
# include "ft_printf.h"
# include "bass.h"

# define WINWIDTH 1920
# define WINHEIGHT 1080
# define HALF_WINWIDTH 960
# define HALF_WINHEIGHT 540

# define MINIMAP_SCALE	8
# define MINIMAP_WALL	0x33008000
# define MINIMAP_FLOOR	0x33000000
# define MINIMAP_BG		0x80FFFFFF
# define MINIMAP_USER	0x33FF0000

# define NYANCAT_X				30
# define NYANCAT_Y				15
# define NYANCAT_RAINBOW_SIZE	0.1
# define NYANCAT_RED	0xFD0000
# define NYANCAT_ORANGE	0xFD9800
# define NYANCAT_YELLOW	0xFDFD00
# define NYANCAT_GREEN	0x33FD00
# define NYANCAT_BLUE	0x0098FD
# define NYANCAT_PURPLE	0x6633FD

# define PREV_COOR_SIZE	30
# define UPDATE_COOR	10

# define SPRITE_MOVE_SPEED	0.01
# define BEAR_MOVE_SPEED	0.03
# define CAT_MOVE_SPEED		0.015
# define DOG_MOVE_SPEED		0.02

# define YELLOW 0xFFFF << 8
# define RED 0xFF << 16
# define GREEN 0xFF << 8
# define BLUE  0xFF

# define UNDEFINED	-1
# define SUCCESS	0
# define FAIL		1
# define WALL_RATIO 1.34

# define BONUS_COUNT	2
# define BONUS_US		0

# define IMG_COUNT	6
# define NO			0
# define SO			1
# define EA			2
# define WE			3
# define CI			4
# define FI			5

/**
 * Short Form of the sprite type
 * ZOMBIE : ZO
 * DOOR : DO
 * MELEE : ME
 * GUN : GU
*/
# define ZOM_IDLE				0
# define ZOM_DIE				1
# define ZOM_ATTACK				2
# define ZOM_WALK				3
# define DOOR_CLOSE				4
# define DOOR_OPEN				5	
# define MELEE_IDLE				6
# define MELEE_ATTACK			7
# define MELEE_WALK				8
# define GUN_IDLE				9
# define GUN_ATTACK				10
# define GUN_WALK				11
# define DANCING_BEAR			12
# define DANCING_DOG			13
# define DANCING_CAT			14
# define PEPSI_DRAW				15
# define PEPSI_IDLE				16
# define PEPSI_DRINK			17
# define PEPSI_OPEN_AND_DRINK	18
# define PEPSI_RUN				19
# define PEPSI_WALK				20

/* user_states */
# define STATE_DRAW				0
# define STATE_IDLE				1
# define STATE_DRINK			2
# define STATE_OPEN_AND_DRINK	3
# define STATE_RUN				4
# define STATE_WALK				5

/* door_state */
# define DOOR_STILL	2

/* mouse_buttons */
# define LEFT_CLICK				1

# define ATTACK			"Attack"
# define DIE			"Die"
# define IDLE			"Idle"
# define WALK			"Walk"
# define CLOSE			"Close"
# define OPEN			"Open"

/* pepsi */
# define DRAW			"Draw"
# define DRINK			"Drink"
# define OPEN_AND_DRINK	"Open_and_drink"
# define RUN			"Run"

# define NORTH	0
# define SOUTH	1
# define EAST	2
# define WEST	3
# define SKY	4
# define FLOOR	5

# define LEFT_UP		0
# define RIGHT_UP		1
# define LEFT_DOWN		2
# define RIGHT_DOWN		3

# define A	0
# define S	1
# define D	2
# define W	13
# define ESC	53
# define SPACE	49
# define ONE	18
# define TWO	19
# define THREE	20
# define FOUR	21
# define SHIFT	257
# define WEAPON_OFFSET	17

# define INT_MAX	0x7FFFFFFF
# define INT_MIN	0x80000000

# define HITBOX			0.3
# define LEFT_ARROW		123
# define RIGHT_ARROW	124
# define DOWN_ARROW		125
# define UP_ARROW		126

# define ARROW_OFFSET	123

# define NUM_SPRITE	21
# define NUM_SPRITE_TYPE	4

/* user */
# define MOVE_SPEED	0.05
# define RUN_SPEED	0.08
# define ROT_SPEED	0.0005

# define E_INTERACT	14

/* user->flag */
# define JUMP 1
# define DIAGONAL 2

# define DIAGONAL_SCALE 0.7071

# define INTERACT_DISTANCE 1

/* BASS_sound_stream */
# define NUM_STREAM				5
# define BG_SOUND				0
# define DRINK_SOUND			1
# define OPEN_AND_DRINK_SOUND	2
# define WALK_SOUND				3
# define RUN_SOUND				4

/* Map Texture */
# define EMPTY				'0'
# define WALL				'1'
# define VDOOR_CLOSED		'V'
# define HDOOR_CLOSED		'H'
# define VDOOR_OPEN			2
# define HDOOR_OPEN 		3
# define CHANGING_VDOOR		4
# define CHANGING_HDOOR		5

# define SKY_WIDTH	2560
# define SKY_HEIGHT	1920

typedef struct s_mlx		t_mlx;
typedef struct s_data		t_data;
typedef struct s_map		t_map;
typedef struct s_pic		t_pic;
typedef struct s_sprite		t_sprite;
typedef struct s_user		t_user;
typedef struct s_block		t_block;
typedef struct s_line_lst	t_line_lst;
typedef struct s_lst_head	t_lst_head;
typedef struct s_node		t_node;
typedef struct s_p_queue	t_p_queue;

/**
 * arr size is vector
*/
typedef struct s_p_queue
{
	t_node	**arr;
	int		size;
	int		max_size;
}	t_p_queue;


typedef struct s_task
{
	void			(*function)(void *);
	void			*arg;
	struct s_task	*next;
	struct s_task	*prev;
}	t_task;

typedef struct s_task_queue
{
	t_task	*head;
	t_task	*tail;
	int		size;
}	t_task_queue;

typedef struct s_thread_pool
{
	pthread_t		*threads;
	t_task_queue	queue;
	int				num_threads;
	pthread_mutex_t	mutex;
	pthread_cond_t	condition;
	pthread_cond_t	synchronize;
	int				task_complete;
	int				total_task;
	bool			shutdown;
}	t_thread_pool;

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
	t_mlx	*mlx;
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
	int		start_i;
	int		end_i;
}	t_floor;

typedef struct s_sprite_node
{
	float		x;
	float		y;
	float		distance;
	int			sprite_type;
	int		v_move_screen;
	float	v_move;
	size_t		start_frame;
	t_p_queue	open_list;
	t_p_queue	close_list;
	t_node		*next_node;
}	t_sprite_node;

typedef struct s_sprite_vec
{
	int				size;
	int				malloc_size;
	t_sprite_node	**list;
}	t_sprite_vec;

/**
 * @var int		num_img		number of img, dynamic init
*/
typedef struct s_sprite {
	int		num_img;
	t_pic	*img;
	size_t	fpm;
}	t_sprite;

/**
 * 
*/
typedef struct s_block {
	t_pic	pic[IMG_COUNT];
	t_pic	bonus[BONUS_COUNT];
	int		f_trgb;
	int		c_trgb;
}	t_block;

typedef struct	s_minimap {
	t_mlx	*mlx;
	float	sin_user;
	float	cos_user;
	float	pixel_y;
	float	pixel_size;
	int		map_position_y;
	int		start_y;
	int		end_y;
	int		start_x;
	int		end_x;
	int		coord_start;
	int		coord_end;
}	t_minimap;

typedef struct s_coord {
	float	x;
	float	y;
}	t_coord;

typedef struct s_position {
	int		x;
	int		y;
}	t_position;

typedef struct s_node
{
	t_position	position;
	t_position	dir;
	float		f_cost;
	float		g_cost;
	int			direction;
	t_node		*next;
}	t_node;


/**
 * @var	float		x			x position of the user
 * @var	float		y			y position of the user
 * @var	float		z			z position of the user
 * @var	int			map_x		x position of the square the user is currently in
 * @var	int			map_y		y position of the square the user is currently in
 * @var	float		dir_x		x component of direction vector of the user
 * @var	float		dir_y		y component of direction vector of the user
 * @var	float		plane_x		x component of direction vector of the plane
 * @var	float		plane_y		y component of direction vector of the plane
 * @var	float		move_speed	the move_speed of the user when up, down ey pressed
 * @var	float		rot_speed	the rotation speed of the user
 * @var float 		z_velocity	the velocity of the user in the z direction
 * @var float		z_gravity	the gravity of the user in the z direction
 * @var t_coordi	last_coor	the last 30 coordinate of the user
 * @var int			last_coor_idx	the index of the last_coordinate
 * @var int			last_coor_size	the size of the last_coordinate
*/
typedef struct s_user {
	float		x;
	float		y;
	float		z;
	float		dir_x;
	float		dir_y;
	float		new_displacement_y;
	float		new_displacement_x;
	float		plane_x;
	float		plane_y;
	float		move_speed;
	float		rot_speed;
	float		zx;
	float		zy;
	int			flag;
	float		z_velocity;
	float		z_gravity;
	t_coord		last_coor[PREV_COOR_SIZE];
	int			last_coor_idx;
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
	t_mlx			*mlx;
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
	int				map_x;
	int				map_y;
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
	int				end_pixel_x;
	bool			changing_door;
	t_pic			*texture;
}	t_dda;

typedef struct s_weapon_thread
{
	int		draw_start;
	int		draw_end;
	int		tex_x;
	int		tex_y;
	t_mlx	*mlx;
	t_pic	*texture;
}	t_weapon_thread;

typedef struct s_sprite_thread
{
	int				draw_start;
	int				draw_end;
	int				tex_x;
	int				tex_y;
	t_mlx			*mlx;
	t_sprite_node	*node;
}	t_sprite_thread;

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
	t_pic	*texture;
}	t_sprite_info;

typedef struct s_door
{
	int			index;
	int			direction;
	int			frame_num;
	size_t		start_frame;
}	t_door;

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
	bool			key_states[UINT16_MAX];
	t_data			img_data[3];
	size_t			interact_frame;
	int				cur_audio;
	int				frame_sync_counter;
	int				num_frame;
	int				num_frame_render;
	int				weapon_num;
	int				change_weapon_num;
	int				pepsi_open;
	size_t			weapon_start_frame;
	int				user_state;
	int				weapon_sprite[5];
	int				*door_map;
	int				num_door;
	long			num_threads;
	float			z_buffer[WINWIDTH];
	size_t			total_frame;
	pthread_t		render_thread;
	pthread_cond_t	render_cond;
	pthread_mutex_t	counter_mutex;
	t_thread_pool	pool;
	t_map			map;
	t_pic			minimap;
	t_block			block;
	t_sprite		sprite[NUM_SPRITE];
	t_sprite_info	sprite_info;
	t_sprite_vec	sprite_vec;
	t_door			*door;
	t_user			user;
	t_dda			dda;
	HSTREAM			sound_stream[NUM_STREAM];
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
DIR				*open_folder(char *path);
int				count_folder_file(DIR *dir);

/* free_pointer_bonus.c */
void			free_2d_ptr(char **ptr);

/* init_struct_bonus.c */
void			init_block(t_block *block);
void			init_pic(t_pic *pic);
void			init_user(t_user *user, float x, float y, char pos);
t_line_lst		*init_line_lst(char *line);

/* free_struct_bonus.c */
void			free_line_lst(t_line_lst *lst);

/* ft_lib_bonus.c */
int				ft_sanitize_enter(char *line);
void			ft_exit(char *str);

/* cub_to_struct_bonus.c */
int				cub_to_struct(char *file, t_mlx *mlx);

/* cub_slice_bonus.c */
int				slice_cub(char *line, t_mlx *graphic, t_block *block);

/* cub_slice_sprite_bonus.c */
int				slice_sprite_cub(char **split, t_mlx *mlx);

/* cub_check_bonus.c */
int				check_img_cub(char **split, t_mlx *graphic, t_pic *org_img);
void			check_img_sprite_file(char *file,
					t_mlx *graphic, t_pic *org_img);

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
void			cub_valid_door_user_zombie(t_map *map);

/* init_struct_bonus.c */
void			get_img_addr(t_data *data);

/* frame_bonus.c */
void			display_frame(t_mlx *graphic);
void			init_frame_thread(t_mlx *graphic);

/* game_loop_bonus.c */
int				game_loop(void *arg);

/* init_dda_data_bonus.c */
void			init_data(t_dda *dda, t_user *user, int x_pixel_num);

/* handle_keypress_bonus.c */
int				handle_keypress(int keycode, void *arg);
size_t			get_time_in_us(void);

/* handle_mouse_bonus.c */
int				handle_mouse_click(int button, int x, int y, void *arg);

/* handle_arrow_bonus.c */
void			check_collision(t_mlx *graphic);

/* collision_check_bonus.c */
void			dir_y_check_p(t_map *map, t_user *user);
void			dir_y_check_n(t_map *map, t_user *user);
void			dir_x_check_p(t_map *map, t_user *user);
void			dir_x_check_n(t_map *map, t_user *user);

/* p_queue_bonus.c */
void			node_swap(t_node **arr, int i, int j);
void			max_heapify(t_p_queue *heap, int i);
t_node			*dequeue(t_p_queue *heap);
void			increase_value(t_p_queue *heap, int i, t_node *node);
void			enqueue(t_p_queue *heap, t_node *node);

/*p_queue_helper.c */
float			distance(float x, float y, float dest_x, float dest_y);
t_p_queue		*init_p_queue(int size);
/* queue_bonus.c */
t_node			*pop(t_p_queue *heap);
void			push(t_p_queue *heap, t_node *node);
t_p_queue		*init_p_queue(int size);
void			sanitize_p_queue(t_p_queue *heap);

/* draw_sprite_bonus.c */
void			draw_sprite(void *arg);
void			update_sprite(t_mlx *graphic, t_user *user);

/* mergesort_sprite_bonus.c */
t_sprite_node	**mergesort_sprite_list(t_sprite_node **list, int size);

/* sprite_list_bonus.c */
void			init_sprite_vec(t_sprite_vec *vec);
void			push_sprite(t_sprite_vec *vec, t_sprite_node *node);
t_sprite_node	*get_sprite(t_sprite_vec *vec, int index);
void			delete_sprite(t_sprite_vec *vec, int index);
t_sprite_node	*create_sprite_node(float x, float y,
					int sprite_type, float v_move);

/* mouse_move_bonus.c */
int				handle_mouse_move(int x, int y, void *arg);

/* task_queue_bonus.c */
t_task			*create_task(void (*function)(void *), void *arg);
void			add_task(t_thread_pool *pool, t_task *task);
t_task			*pop_task(t_thread_pool *pool);

/* thread_pool_bonus.c */
void			thread_pool_init(t_thread_pool *pool, int num_threads);
void			thread_pool_shutdown(t_thread_pool *pool);
void			start_wait_for_threads(t_thread_pool *pool, int total_task);
void			wait_for_threads(t_thread_pool *pool);

/* draw_wall_bonus.c */
void			draw_wall_routine(void *arg);
bool			is_open_door(int door_num);

/* draw_walls_thread.c */
void			draw_wall_thread(t_mlx *graphic);

/* draw_sprite_thread.c */
void			draw_sprite_thread(t_mlx *graphic, t_pic *texture,
					t_sprite_node *cur_sprite);

/* draw_minimap_thread.c */
void			draw_minimap_thread(t_mlx *graphic);
void			count_user_coordinate(t_mlx *mlx, t_minimap *info);
t_minimap		*draw_minimap_thread_helper(t_minimap *info,
					t_mlx *graphic, int i);

/* handle_keyrelease.c */
int				handle_keyrelease(int keycode, void *arg);

/* handle_keys_bonus.c */
void			handle_keys_loop(t_mlx *graphic);

/* handle_jump_bonus.c */
void			handle_jump(t_mlx *graphic, t_user *user);

/* sprite_distance_bonus.c */
void			update_sprite_distance(t_mlx *graphic,
					t_user *user, t_sprite_vec *vec);

/* sound_bonus.c */
void			set_bg_sound(t_mlx *graphic);
void			load_sound(t_mlx *mlx);
void			play_sound(t_mlx *mlx, int audio_num);

/* draw_minimap_bonus.c */
void			draw_minimap_routine(void *in);
void			init_minimap(t_pic *minimap);

/* draw_user_bonus.c */
void			draw_user(t_mlx *graphic);

/* open_file.c */
int				open_file(char *file);
int				close_file(int fd);

/* draw_user_util_bonus */
void			change_weapon(t_mlx *graphic);
void			change_state(t_mlx *graphic, int user_state);

/* init_bonus.c */
void			init_sprite_fpm(t_mlx *graphic);

/* parse_door_map_bonus.c */
void			parse_door_map(t_mlx *graphic);

/* door_interaction_bonus.c */
void			check_door_interaction(t_mlx *graphic, t_dda *dda, t_map *map);

/* door_map_bonus.c */
t_door			*get_door(t_mlx	*graphic, int y, int x);

/* door_dda_bonus.c */
void			perform_door_dda(t_dda *dda, t_map *map);
void			update_door(t_mlx *graphic);

void			jps(t_mlx *mlx);

/* calculate_sprite_bonus.c */
void			calculate_sprite(t_sprite_info *sprite,
					t_sprite_node *node, t_user *user);

/* door_util_bonus.c */
bool			is_open_door(int door_num);
bool			is_v_door(int map_texture);
bool			is_h_door(int map_texture);
void			check_interaction_opendoor(t_mlx *graphic,
					t_dda *dda, t_map *map);

/* perform_dda_bonus.c */
void			perform_dda(t_mlx *graphic, t_dda *dda, t_map *map);

#endif
