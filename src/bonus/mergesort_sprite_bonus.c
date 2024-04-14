/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mergesort_sprite_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:09:32 by jacob             #+#    #+#             */
/*   Updated: 2024/04/14 23:38:59 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	mergesort_sprite_sub_helper(t_sprite_node **list,
	t_sprite_node **fill, int size)
{
	int	i;

	i = -1;
	while (++i < size)
		list[i] = fill[i];
}

static void	mergesort_sprite_sublist(t_sprite_node **list, t_sprite_node **left,
	t_sprite_node **right, int size)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < size / 2 && j < size - (size / 2))
	{
		if (left[i]->distance <= right[j]->distance)
		{
			list[i + j] = right[j];
			j++;
		}
		else
		{
			list[i + j] = left[i];
			i++;
		}
	}
	if (i >= size / 2)
		mergesort_sprite_sub_helper(&list[i + j],
			&right[j], size - (size / 2) - j);
	else
		mergesort_sprite_sub_helper(&list[i + j], &left[i], (size / 2) - i);
}

t_sprite_node	**mergesort_sprite_list(t_sprite_node **list, int size)
{
	t_sprite_node	**left;
	t_sprite_node	**right;
	int				j;
	int				i;

	if (size <= 1)
		return (list);
	left = malloc(sizeof(t_sprite_node *) * (size / 2));
	right = malloc(sizeof(t_sprite_node *) * (size - (size / 2)));
	i = -1;
	while (++i < size / 2)
		left[i] = list[i];
	j = -1;
	while (++j < size - (size / 2))
		right[j] = list[i + j];
	left = mergesort_sprite_list(left, size / 2);
	right = mergesort_sprite_list(right, size - (size / 2));
	mergesort_sprite_sublist(list, left, right, size);
	free(left);
	free(right);
	return (list);
}
