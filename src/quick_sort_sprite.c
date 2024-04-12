/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quick_sort_sprite.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:09:32 by jacob             #+#    #+#             */
/*   Updated: 2024/04/12 17:01:37 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	swap(t_sprite_order *p1, t_sprite_order *p2)
{
	float	num_temp;
	int		index_temp;

	num_temp = p1->num;
	index_temp = p1->index;
	p1->num = p2->num;
	p1->index = p2->index;
	p2->num = num_temp;
	p2->index = index_temp;
}

static int	partition(t_sprite_order *arr, int low, int high)
{
	float	pivot;
	int		i;
	int		j;

	pivot = arr[NUM_SPRITE].num;
	i = low - 1;
	j = low - 1;
	while (++j <= high)
	{
		if (arr[j].num < pivot)
		{
			i++;
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[j]);
	return (i + 1);
}

void	quick_sort_sprite(t_sprite_order *arr, int low, int high)
{
	int	pivot;

	if (low < high)
	{
		pivot = partition(arr, low, high);
		quick_sort_sprite(arr, low, pivot - 1);
		quick_sort_sprite(arr, pivot + 1, high);
	}
}
