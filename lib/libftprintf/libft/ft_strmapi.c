/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 11:42:20 by minsepar          #+#    #+#             */
/*   Updated: 2023/10/07 14:57:49 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		len;
	char	*return_str;
	int		i;

	i = 0;
	if (!s || !f)
		return (0);
	len = ft_strlen(s);
	return_str = (char *)malloc(len + 1);
	if (!return_str)
		return (0);
	while (i < len)
	{
		return_str[i] = f(i, s[i]);
		i++;
	}
	return_str[i] = 0;
	return (return_str);
}
