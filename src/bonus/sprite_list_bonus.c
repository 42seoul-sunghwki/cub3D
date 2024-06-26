/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_list_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 15:37:32 by minsepar          #+#    #+#             */
/*   Updated: 2024/05/09 13:36:07 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	init_sprite_vec(t_sprite_vec *vec)
{
	vec->malloc_size = 10;
	vec->size = 0;
	vec->list = malloc(sizeof(t_sprite_node *) * 10);
}

void	push_sprite(t_sprite_vec *vec, t_sprite_node *node)
{
	t_sprite_node	**new_list;
	int				i;

	if (vec->size == vec->malloc_size)
	{
		vec->malloc_size *= 2;
		new_list = malloc(sizeof(t_sprite_node *) * vec->malloc_size);
		i = -1;
		while (++i < vec->size)
			new_list[i] = vec->list[i];
		free(vec->list);
		vec->list = new_list;
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

t_sprite_node	*create_sprite_node(float x, float y,
	int sprite_type, float v_move)
{
	t_sprite_node	*return_node;

	return_node = malloc(sizeof(t_sprite_node));
	return_node->x = x + HITBOX;
	return_node->y = y + HITBOX;
	return_node->v_move = v_move;
	return_node->sprite_type = sprite_type;
	return_node->start_frame = 0;
	return_node->open_list.max_size = 10;
	return_node->open_list.size = 0;
	return_node->open_list.arr = (t_node **)calloc(10, sizeof(t_node *));
	return_node->close_list.max_size = 10;
	return_node->close_list.size = 0;
	return_node->close_list.arr = (t_node **)calloc(10, sizeof(t_node *));
	return_node->next_node = NULL;
	return (return_node);
}
