/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:13:58 by minsepar          #+#    #+#             */
/*   Updated: 2023/10/10 11:34:24 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*joined_str;

	if (!s1 || !s2)
		return (0);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	joined_str = (char *)malloc(s1_len + s2_len + 1);
	if (!joined_str)
		return (0);
	joined_str[0] = 0;
	ft_strlcat(joined_str, s1, s1_len + 1);
	ft_strlcat(joined_str, s2, s1_len + s2_len + 1);
	joined_str[s1_len + s2_len] = 0;
	return (joined_str);
}
