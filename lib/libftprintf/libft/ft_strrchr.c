/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 13:48:59 by minsepar          #+#    #+#             */
/*   Updated: 2023/10/10 15:54:51 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	s_len;

	c %= 256;
	s_len = ft_strlen(s);
	while (s_len >= 0)
	{
		if (s[s_len] == c)
			return ((char *) s + s_len);
		s_len--;
	}
	return (0);
}
