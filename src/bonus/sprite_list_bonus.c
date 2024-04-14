/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_list_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 15:37:32 by minsepar          #+#    #+#             */
/*   Updated: 2024/04/14 18:24:32 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	push_sprite(t_sprite_vec *vec, t_sprite_node *node)
{
	t_sprite_node	**new_list;
	int				i;

	if (vec->size == vec->malloc_size)
	{
		vec->malloc_size *= 2;
		new_list = malloc(sizeof(t_sprite_node *) * (vec->malloc_size + 1));
		i = -1;
		while (++i < vec->size)
			new_list[i] = vec->list[i];
	}
	vec->list[vec->size] = node;
	vec->size++;
}

t_sprite_node	*get_sprite(t_sprite_vec *vec, int index)
{
	if (index >= vec->size)
		return (NULL);
	return (vec->list[index]);
}

void	delete_sprite(t_sprite_vec *vec, int index)
{
	if (index >= vec->size)
		return ;
	free(vec->list[index]);
	vec->list[index] = vec->list[--vec->size];
}
