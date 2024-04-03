/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:35:53 by minsepar          #+#    #+#             */
/*   Updated: 2023/10/07 16:50:24 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	p1;
	size_t	i;
	size_t	len_needle;

	i = 0;
	p1 = 0;
	if (!needle[0])
		return ((char *) haystack);
	if (len == 0)
		return (0);
	len_needle = ft_strlen(needle);
	while (haystack[p1] && p1 + len_needle <= len)
	{
		while (haystack[p1 + i]
			&& haystack[p1 + i] == needle[i])
			i++;
		if (!needle[i])
			return ((char *) haystack + p1);
		p1++;
		i = 0;
	}
	return (0);
}
