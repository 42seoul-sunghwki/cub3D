/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:16:25 by minsepar          #+#    #+#             */
/*   Updated: 2023/10/09 12:10:39 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*s_char;
	unsigned int	uc;
	size_t			i;

	uc = c;
	uc %= 256;
	i = 0;
	s_char = (unsigned char *)s;
	while (i < n)
	{
		if (s_char[i] == uc)
			return ((void *) &s_char[i]);
		i++;
	}
	return (0);
}
