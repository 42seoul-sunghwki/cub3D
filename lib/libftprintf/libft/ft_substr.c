/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:38:26 by minsepar          #+#    #+#             */
/*   Updated: 2023/10/07 20:17:11 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_substr_helper(void)
{
	char	*s_cpy;

	s_cpy = (char *)malloc(1);
	if (!s_cpy)
		return (0);
	s_cpy[0] = 0;
	return (s_cpy);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*s_cpy;

	i = 0;
	if (!s)
		return (0);
	if (start >= ft_strlen(s))
		return (ft_substr_helper());
	if (ft_strlen(s) - start < len)
		len = ft_strlen(s) - start;
	s_cpy = (char *)malloc(len + 1);
	if (!s_cpy)
		return (s_cpy);
	while (s[start + i] && i < len)
	{
		s_cpy[i] = s[start + i];
		i++;
	}
	s_cpy[i] = 0;
	return (s_cpy);
}
