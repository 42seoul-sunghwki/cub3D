/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:24:07 by minsepar          #+#    #+#             */
/*   Updated: 2023/10/07 15:02:01 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*s_uc1;
	const unsigned char	*s_uc2;
	size_t				i;

	if (n == 0)
		return (0);
	i = 0;
	s_uc1 = s1;
	s_uc2 = s2;
	while (s_uc1[i] == s_uc2[i] && i + 1 < n)
		i++;
	return (s_uc1[i] - s_uc2[i]);
}
