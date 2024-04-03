/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 23:06:35 by minsepar          #+#    #+#             */
/*   Updated: 2023/10/08 23:07:13 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*dst_char;

	i = 0;
	dst_char = dst;
	if (!dst_char && !src)
		return (0);
	if (src <= dst)
	{
		while (len > 0)
		{
			dst_char[len - 1] = *(unsigned char *)(src + len - 1);
			len--;
		}
	}
	else
	{
		while (i < len)
		{
			dst_char[i] = *(unsigned char *)(src + i);
			i++;
		}
	}
	return (dst);
}
