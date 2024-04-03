/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlcat.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 10:30:15 by minsepar          #+#    #+#             */
/*   Updated: 2023/10/10 15:07:36 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dst_len;

	i = 0;
	if (dstsize <= 0)
		return (ft_strlen(src));
	dst_len = ft_strlen(dst);
	while (src[i] && i + dst_len + 1 < dstsize)
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	if (dst_len + i < dstsize)
		dst[dst_len + i] = 0;
	else
		return (ft_strlen(src) + dstsize);
	return (dst_len + ft_strlen(src));
}
