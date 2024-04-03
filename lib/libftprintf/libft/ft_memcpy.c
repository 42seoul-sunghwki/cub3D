/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 22:30:38 by minsepar          #+#    #+#             */
/*   Updated: 2023/10/06 21:37:37 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*dst_char;

	i = 0;
	dst_char = dst;
	while (!(!dst && !src) && i < n)
	{
		dst_char[i] = *(unsigned char *) src;
		src++;
		i++;
	}
	return (dst);
}
