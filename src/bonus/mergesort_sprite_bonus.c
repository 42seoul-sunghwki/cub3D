/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mergesort_sprite_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:09:32 by jacob             #+#    #+#             */
/*   Updated: 2024/04/14 20:36:32 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_sprite_node	**mergesort_sprite_vec(t_sprite_vec *vec, int start, int end,
	int right_start)
{
	t_sprite_node	**temp_list;
	t_sprite_node	**left_list;
	t_sprite_node	**right_list;
	int				mid;
	int				list_i;

	mid = (end + start) / 2;
	right_start = mid;
	list_i = 0;
	left_list = 0;
	right_list = 0;
	if ((end - start) > 1)
	{
		left_list = mergesort_sprite_vec(vec, start, mid, (mid + start) / 2);
		right_list = mergesort_sprite_vec(vec, mid, end, (mid + end) / 2);
	}
	temp_list = malloc(sizeof(t_sprite_node *) * (end - start));
	while (start < mid && right_start < end)
	{
		if (left_list[start]->distance <= right_list[right_start]->distance)
			temp_list[list_i++] = left_list[start++];
		else
			temp_list[list_i++] = right_list[right_start++];
	}
	while (start < mid)
	{
		temp_list[list_i++] = vec->list[start++];
	}
	while (right_start < end)
	{
		temp_list[list_i++] = vec->list[right_start++];
	}
	printf("---------\n");
	for (int i = 0; i < list_i; i++)
	{
		printf("[%f]\n", temp_list[i]->distance);
	}
	if (left_list)
		free(left_list);
	if (right_list)
		free(right_list);
	return (temp_list);
}
