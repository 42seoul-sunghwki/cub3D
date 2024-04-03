/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 11:49:56 by minsepar          #+#    #+#             */
/*   Updated: 2023/10/07 16:27:43 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	c %= 256;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return ((char *) s + i);
		i++;
	}
	if (!c)
		return ((char *) s + ft_strlen(s));
	return (0);
}
