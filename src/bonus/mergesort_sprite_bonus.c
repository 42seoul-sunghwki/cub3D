/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mergesort_sprite_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:09:32 by jacob             #+#    #+#             */
/*   Updated: 2024/04/14 21:46:58 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	merge_sort_sprite_node_divide(t_sprite_node **tmp, t_sprite_node **left,
		t_sprite_node **right, int size)
{
	int				i;
	int				j;

	if (size <= 1)
		return (tmp);
	i = -1;
	while (++i < size / 2)
		left[i] = tmp[i];
	j = -1;
	while (++j < size - size / 2)
		right[j] = tmp[i + j];
	left = merge_sort_sprite_node(left, size / 2);
	right = merge_sort_sprite_node(right, size - size / 2);
}

void	merge_sort_sprite_node_conquer(t_sprite_node **tmp,
		t_sprite_node **left, t_sprite_node **right, int size)
{
	int				i;
	int				j;

	i = 0;
	j = 0;
	while (i < size / 2 && j < size - size / 2)
	{
		if (left[i]->distance < right[j]->distance)
		{
			tmp[i + j] = left[i];
			i++;
		}
		else
		{
			tmp[i + j] = right[j];
			j++;
		}
	}
	while (i < size / 2)
	{
		tmp[i + j] = left[i];
		i++;
	}
	while (j < size - size / 2)
	{
		tmp[i + j] = right[j];
		j++;
	}
}

t_sprite_node	**merge_sort_sprite_node(t_sprite_node **tmp, int size)
{
	t_sprite_node	**left;
	t_sprite_node	**right;
	int				i;
	int				j;

	left = (t_sprite_node **)malloc(sizeof(t_sprite_node *) * (size / 2));
	right = (t_sprite_node **)malloc(sizeof(t_sprite_node *) * (size - size / 2));
	merge_sort_sprite_node_divide(tmp, left, right, size);
	merge_sort_sprite_node_conquer(tmp, left, right, size);
	free(left);
	free(right);
	return (tmp);
}

void	mergesort_sprite_vec(t_sprite_vec *vec, int start, int end)
{
	t_sprite_node	**tmp;

	tmp = vec->list;
	tmp = merge_sort_sprite_node(tmp, end - start);
}
