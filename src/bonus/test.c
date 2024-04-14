/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 19:08:07 by minsepar          #+#    #+#             */
/*   Updated: 2024/04/14 21:38:01 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main()
{
	t_sprite_node	*temp;
	t_sprite_vec	vec;
	//t_sprite_node	**list;

	init_sprite_vec(&vec);
	printf("vec: %p\n", vec.list);
	for (int i = 10; i > 0; i--)
	{
		temp = create_sprite_node(i, 0, 0);
		printf("temp: [%p]\n", temp);
		temp->distance = i;
		push_sprite(&vec, temp);
	}
	mergesort_sprite_vec(&vec, 0, vec.size);
	for (int i = 0; i < 10; i++)
	{
		temp = get_sprite(&vec, i);
		printf("%f\n", temp->distance);
	}
}
