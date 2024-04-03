/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 19:35:13 by minsepar          #+#    #+#             */
/*   Updated: 2023/10/10 15:59:34 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	init(int *i, int *j, int *len, char const *s1)
{
	*i = 0;
	*j = 0;
	*len = ft_strlen(s1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		len;
	char	*return_ptr;

	if (!s1 || !set)
		return (0);
	init(&i, &j, &len, s1);
	while (i < len && ft_strchr(set, s1[i]))
		i++;
	if (i == len)
		return (ft_strdup(""));
	while (ft_strrchr(set, s1[len - 1]))
		len--;
	return_ptr = (char *)malloc(len - i + 1);
	if (!return_ptr)
		return (0);
	while (i < len)
	{
		return_ptr[j] = s1[i];
		i++;
		j++;
	}
	return_ptr[j] = 0;
	return (return_ptr);
}
