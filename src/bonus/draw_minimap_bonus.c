/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 13:02:09 by sunghwki          #+#    #+#             */
/*   Updated: 2024/04/28 16:31:09 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	rotate_minimap(t_minimap *minimap, float pixel_x, float *rotate_x, float *rotate_y)
{
	float	vec_x;
	float	vec_y;
	float	rotate_vec_x;
	float	rotate_vec_y;

	vec_x = pixel_x - minimap->mlx->user.x;
	vec_y = minimap->pixel_y - minimap->mlx->user.y;
	rotate_vec_x = minimap->cos_user * vec_y
		+ minimap->sin_user * vec_x;
	rotate_vec_y = minimap->sin_user * vec_y
		- minimap->cos_user * vec_x;
	*rotate_x = rotate_vec_x + minimap->mlx->user.x;
	*rotate_y = rotate_vec_y + minimap->mlx->user.y;
}

void	count_user_coordinate(t_mlx *mlx)
{
	t_user	*user;

	user = &mlx->user;
	if (mlx->total_frame % UPDATE_COOR == 0)
	{
		mlx->user.last_coor[user->last_coor_idx].x = mlx->user.x;
		mlx->user.last_coor[user->last_coor_idx].y = mlx->user.y;
		mlx->user.last_coor_idx = (mlx->user.last_coor_idx + 1)
			% PREV_COOR_SIZE;
	}
}

/**
 * @brief Get next user last coordinate not same as current coordinate
*/
t_coord	*get_next_user_last_coor(t_mlx *mlx, int *idx)
{
	int		i;
	t_coord	*coor;

	i = *idx;
	coor = mlx->user.last_coor;
	while (*idx != mlx->user.last_coor_idx)
	{
		*idx = (*idx + 1) % PREV_COOR_SIZE;
		if (coor[i].x != coor[*idx].x && coor[i].y != coor[*idx].y)
			return (&coor[*idx]);
	}
	return (NULL);
}

//static float	get_distance(t_coord *start, t_coord *end, t_coord *coor)
//{
//	float	a;
//	float	b;
//	float	c;

//	a = end->y - start->y;
//	b = start->x - end->x;
//	c = b * start->y - a * start->x;
//	return (fabs(a * coor->x + b * coor->y + c) / sqrt(a * a + b * b));
//}

//static float	get_right_left_vec(t_coord *start, t_coord *end, t_coord *coor)
//{
//	float	vec_x;
//	float	vec_y;
//	float	coor_vec_x;
//	float	coor_vec_y;

//	vec_x = end->x - start->x;
//	vec_y = end->y - start->y;
//	coor_vec_x = coor->x - start->x;
//	coor_vec_y = coor->y - start->y;
//	return (vec_x * coor_vec_y - vec_y * coor_vec_x);
//}

//static void	draw_rainbow_minimap(t_mlx *mlx, t_coord *pixel, int minimap_x, int minimap_y)
//{
//	int		i;
//	int		start;
//	float	distance;
//	float	right_left;
//	t_user	*user;
//	t_coord	*coor;

//	user = &mlx->user;
//	i = (user->last_coor_idx + 1) % PREV_COOR_SIZE;
//	start = i;
//	while (i != mlx->user.last_coor_idx)
//	{
//		coor = get_next_user_last_coor(mlx, &i);
//		if (coor == NULL)
//			break ;
//		distance = get_distance(&mlx->user.last_coor[start], coor, pixel);
//		right_left = get_right_left_vec(&mlx->user.last_coor[start], coor, pixel);
//		if (distance <= NYANCAT_RAINBOW_SIZE * 3)
//		{
//			if (distance > NYANCAT_RAINBOW_SIZE * 2)
//			{
//				if (right_left > 0)
//					my_mlx_pixel_put(&mlx->img_data[mlx->num_frame], minimap_x, minimap_y, NYANCAT_RED);
//				else
//					my_mlx_pixel_put(&mlx->img_data[mlx->num_frame], minimap_x, minimap_y, NYANCAT_PURPLE);
//			}
//			else if (distance > NYANCAT_RAINBOW_SIZE)
//			{
//				if (right_left > 0)
//					my_mlx_pixel_put(&mlx->img_data[mlx->num_frame], minimap_x, minimap_y, NYANCAT_ORANGE);
//				else
//					my_mlx_pixel_put(&mlx->img_data[mlx->num_frame], minimap_x, minimap_y, NYANCAT_BLUE);
//			}
//			else
//			{
//				if (right_left > 0)
//					my_mlx_pixel_put(&mlx->img_data[mlx->num_frame], minimap_x, minimap_y, NYANCAT_YELLOW);
//				else
//					my_mlx_pixel_put(&mlx->img_data[mlx->num_frame], minimap_x, minimap_y, NYANCAT_GREEN);
//			}
//			return ;
//		}
//		start = i;
//		i = (i + 1) % PREV_COOR_SIZE;
//	}
//}

static void	draw_rotate_minimap(t_mlx *mlx, t_coord *pixel,
		int minimap_x, int minimap_y)
{
	t_data	*minimap;
	int		tmp;
	int		get_trgb;

	minimap = &mlx->img_data[mlx->num_frame];
	if (pixel->y < 0 || pixel->y >= mlx->map.h
		|| pixel->x < 0 || pixel->x >= mlx->map.w)
	{
		get_trgb = my_mlx_pixel_get(minimap, minimap_x, minimap_y);
		tmp = blend_trgb(MINIMAP_BG, get_trgb);
		my_mlx_pixel_put(minimap, minimap_x, minimap_y, tmp);
	}
	else if (mlx->map.map[(int)pixel->y][(int)pixel->x] == '1')
		my_mlx_pixel_put(minimap, minimap_x, minimap_y, MINIMAP_WALL);
	else
		my_mlx_pixel_put(minimap, minimap_x, minimap_y, MINIMAP_FLOOR);
	
	if (minimap_x > mlx->minimap.w / 2 - NYANCAT_X && minimap_x < mlx->minimap.w / 2 + NYANCAT_X
		&& minimap_y > mlx->minimap.h / 2 - NYANCAT_Y && minimap_y < mlx->minimap.h / 2 + NYANCAT_Y)
	{
		get_trgb = my_mlx_pixel_get(&(mlx->block.bonus[BONUS_US].data), (int)((float)mlx->block.bonus[BONUS_US].w / (NYANCAT_X * 2) * (minimap_x - mlx->minimap.w / 2 + NYANCAT_X)), (int)((float)mlx->block.bonus[BONUS_US].h / (NYANCAT_Y * 2) * (minimap_y - mlx->minimap.h / 2 + NYANCAT_Y)));
		if (get_trgb > 0)
			my_mlx_pixel_put(minimap, minimap_x, minimap_y, get_trgb);
	}
}

//static void	draw_rotate_minimap(t_mlx *mlx, float pixel_x, float pixel_y,
//		int minimap_x, int minimap_y)
//{
//	t_data	*minimap;
//	int		tmp;
//	int		get_trgb;

//	minimap = &mlx->img_data[mlx->num_frame];
//	if (pixel_y < 0 || pixel_y >= mlx->map.h
//		|| pixel_x < 0 || pixel_x >= mlx->map.w)
//	{
//		get_trgb = my_mlx_pixel_get(minimap, minimap_x, minimap_y);
//		tmp = blend_trgb(MINIMAP_BG, get_trgb);
//		my_mlx_pixel_put(minimap, minimap_x, minimap_y, tmp);
//	}
//	else if (mlx->map.map[(int)pixel_y][(int)pixel_x] == '1')
//		my_mlx_pixel_put(minimap, minimap_x, minimap_y, MINIMAP_WALL);
//	else
//		my_mlx_pixel_put(minimap, minimap_x, minimap_y, MINIMAP_FLOOR);
//	if (minimap_x > mlx->minimap.w / 2 - NYANCAT_X && minimap_x < mlx->minimap.w / 2 + NYANCAT_X
//		&& minimap_y > mlx->minimap.h / 2 - NYANCAT_Y && minimap_y < mlx->minimap.h / 2 + NYANCAT_Y)
//	{
//		get_trgb = my_mlx_pixel_get(&(mlx->block.bonus[BONUS_US].data), (int)((float)mlx->block.bonus[BONUS_US].w / (NYANCAT_X * 2) * (minimap_x - mlx->minimap.w / 2 + NYANCAT_X)), (int)((float)mlx->block.bonus[BONUS_US].h / (NYANCAT_Y * 2) * (minimap_y - mlx->minimap.h / 2 + NYANCAT_Y)));
//		//printf("get_trgb : %d, minimap_x : %d, minimap_y : %d\n", get_trgb, minimap_x, minimap_y);
//		//printf("pic_x : %d, pic_y : %d\n", mlx->minimap.w / 2 - NYANCAT_X, mlx->minimap.h / 2 - NYANCAT_Y);
//		//printf("NYANCAT_X : %d, NYANCAT_Y : %d\n", mlx->block.bonus[BONUS_US].w / (NYANCAT_X * 2) * (minimap_x - mlx->minimap.w / 2 + NYANCAT_X), mlx->block.bonus[BONUS_US].h / (NYANCAT_Y * 2) * (minimap_y - mlx->minimap.h / 2 + NYANCAT_Y));
//		//printf("nyancat w : %d, nyancat h : %d\n", mlx->block.bonus[BONUS_US].w, mlx->block.bonus[BONUS_US].h);
//		if (get_trgb > 0)
//			my_mlx_pixel_put(minimap, minimap_x, minimap_y, get_trgb);
//	}
//}


/**
 * @brief Draw minimap
 * starting from x - 5, y - 5 as user position (x, y)
 * end from x + 5, y + 5 as user position (x, y)
 * draw movement speed 100 / WINHEIGHT - 1 pixel as MINIMAP_SCALE is 10
*/
void	draw_minimap_routine(void *in)
{
	t_minimap	*minimap;
	t_coord		rotate_coord;
	float		pixel_x;
	int			i;

	minimap = (t_minimap *)in;
	while (minimap->start_y > minimap->end_y)
	{
		i = 0;
		minimap->start_x = minimap->mlx->minimap.w / 2 - sqrt(minimap->mlx->minimap.w * minimap->start_y - minimap->start_y * minimap->start_y);
		minimap->end_x = minimap->mlx->minimap.w - minimap->start_x;
		pixel_x = minimap->mlx->user.x - MINIMAP_SCALE / 2;
		while (i < minimap->end_x)
		{
			if (minimap->start_x > i)
			{
				i += 1;
				pixel_x += minimap->pixel_size;
				continue ;
			}
			rotate_minimap(minimap, pixel_x, &rotate_coord.x, &rotate_coord.y);
			draw_rotate_minimap(minimap->mlx, &rotate_coord, i, minimap->start_y);
			pixel_x += minimap->pixel_size;
			i += 1;
		}
		minimap->start_y--;
		minimap->pixel_y += minimap->pixel_size;
	}
}

//static void	draw_xline_minimap(t_mlx *mlx, float pixel_y,
//			float pixel_size, int start_y)
//{
//	float	i;
//	int		j;
//	t_data	*minimap;
//	float	pixel_x;
//	float	rotate_x;
//	float	rotate_y;

//	j = 0;
//	i = -(float)MINIMAP_SCALE / 2;
//	minimap = &mlx->img_data[mlx->num_frame];
//	while (j < mlx->minimap.w)
//	{
//		pixel_x = mlx->user.x + i;
//		if (pixel_y < 0 || pixel_y >= mlx->map.h
//			|| pixel_x < 0 || pixel_x >= mlx->map.w)
//			my_mlx_pixel_put(minimap,
//				j, start_y, MINIMAP_BG);
//		else if (mlx->map.map[(int)pixel_y][(int)pixel_x] == '1')
//			my_mlx_pixel_put(minimap,
//				j, start_y, MINIMAP_WALL);
//		else
//			my_mlx_pixel_put(minimap,
//				j, start_y, MINIMAP_FLOOR);
//		if (pixel_y - HITBOX < mlx->user.y && mlx->user.y < pixel_y + HITBOX
//			&& pixel_x - HITBOX < mlx->user.x && mlx->user.x < pixel_x + HITBOX)
//			my_mlx_pixel_put(minimap, j, start_y, MINIMAP_USER);
//		i += pixel_size;
//		j++;
//	}
//}


//void	draw_minimap_routine(void *in)
//{
//	t_minimap	*minimap;

//	minimap = (t_minimap *)in;
//	while (minimap->start_y > minimap->end_y)
//	{
//		draw_xline_minimap(minimap->mlx, minimap->pixel_y,
//			minimap->pixel_size, minimap->start_y);
//		minimap->start_y--;
//		minimap->pixel_y += minimap->pixel_size;
//	}
//}

void	init_minimap(t_pic *minimap)
{
	minimap->h = WINWIDTH / MINIMAP_SCALE;
	minimap->w = WINWIDTH / MINIMAP_SCALE;
}
