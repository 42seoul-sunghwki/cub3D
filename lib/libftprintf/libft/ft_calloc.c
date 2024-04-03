/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:39:22 by minsepar          #+#    #+#             */
/*   Updated: 2024/03/06 17:15:45 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*c_ptr;
	size_t	i;

	i = 0;
	c_ptr = (char *)malloc(count * size);
	if (!c_ptr)
		return (NULL);
	while (i < count * size)
		c_ptr[i++] = 0;
	return ((void *) c_ptr);
}
