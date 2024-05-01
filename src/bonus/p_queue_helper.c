/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_queue_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 14:27:17 by sunghwki          #+#    #+#             */
/*   Updated: 2024/05/01 15:20:24 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_p_queue	*init_p_queue(int size)
{
	t_p_queue	*heap;

	heap = (t_p_queue *)malloc(sizeof(t_p_queue));
	heap->arr = (t_node **)malloc(sizeof(t_node *) * (size + 1));
	memset(heap->arr, 0, sizeof(t_node) * (size + 1));
	heap->size = 0;
	return (heap);
}

float	distance(float x, float y, float dest_x, float dest_y)
{
	return (sqrt(pow(dest_x - x, 2) + pow(dest_y - y, 2)));
}

