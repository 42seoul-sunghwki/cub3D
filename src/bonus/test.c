/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 19:08:07 by minsepar          #+#    #+#             */
/*   Updated: 2024/04/14 23:33:56 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main()
{
	t_sprite_node	*temp;
	t_sprite_node	**temp_list;
	t_sprite_vec	vec;
	//t_sprite_node	**list;

	init_sprite_vec(&vec);
	printf("vec: %p\n", vec.list);
	for (int i = 0; i < 10; i++)
	{
		temp = create_sprite_node(i, 0, 0);
		printf("temp: [%p]\n", temp);
		temp->distance = i;
		push_sprite(&vec, temp);
	}
	temp_list = mergesort_sprite_list(vec.list, vec.size);
	for (int i = 0; i < 10; i++)
	{
		// temp = get_sprite(&vec, i);
		printf("%f\n", temp_list[i]->distance);
	}
}
