/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 22:35:17 by sunghwki          #+#    #+#             */
/*   Updated: 2024/04/02 22:37:23 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WINWIDTH 1920
# define WINHEIGHT 1080

/*
* 이중 버퍼링
*/
typedef struct s_mlx {
	void *mlx;
	void *win;
	t_data data[2];
} t_mlx;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_map {
	int w;
	int h;
	int map_x;
	int map_y;
} t_map;

/**
* 이미지 저장
*/
typedef struct s_pic {
	int w;
	int h;
	void *img;
} t_pic;

typedef struct s_sprite {
	int l;
	t_pic *size;
} t_sprite;

typedef struct s_user {
	double x;
	double y;
	double z;
	double dir_x;
	double dir_y;
	double plane_x;
	double plane_y;
	double old_time;
	double new_time;
} t_user;

#endif
