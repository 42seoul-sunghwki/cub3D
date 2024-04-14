/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 19:08:07 by minsepar          #+#    #+#             */
/*   Updated: 2024/04/14 20:19:05 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main()
{
	t_sprite_node	*temp;
	t_sprite_vec	vec;
	t_sprite_node	**list;

	init_sprite_vec(&vec);
	printf("vec: %p\n", vec.list);
	for (int i = 10; i > 0; i--)
	{
		temp = create_sprite_node(i, 0, 0);
		printf("temp: [%p]\n", temp);
		temp->distance = i;
		push_sprite(&vec, temp);
	}
	list = mergesort_sprite_vec(&vec, 0, vec.size, vec.size / 2);
	for (int i = 0; i < 10; i++)
	{
		temp = get_sprite(&vec, i);
		printf("%f\n", temp->distance);
	}
}
