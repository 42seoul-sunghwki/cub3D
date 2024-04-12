/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quick_sort_sprite.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacob <jacob@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:09:32 by jacob             #+#    #+#             */
/*   Updated: 2024/04/12 15:10:32 by jacob            ###   ########.fr       */
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

void	sort_sprite_quick(t_sprite_order *arr, int low, int high)
{
	int	pivot;

	if (low < high)
	{
		pivot = parition(arr, low, high);
		sort_sprite_quick(arr, low, pivot - 1);
		sort_sprite_quick(arr, pivot + 1, high);
	}
}
