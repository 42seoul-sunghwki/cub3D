/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 22:14:58 by minsepar          #+#    #+#             */
/*   Updated: 2023/10/09 12:10:59 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	word_num(char const *s, char c)
{
	int	i;
	int	num_word;

	i = 0;
	num_word = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			num_word++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (num_word);
}

int	ft_split_helper(char const **s, int *i, char c, int *len)
{
	while ((*s)[*i] && (*s)[*i] == c)
		*i = *i + 1;
	if (!(*s)[*i])
		return (0);
	while ((*s)[*i + *len] && (*s)[*i + *len] != c)
		*len = *len + 1;
	return (1);
}

char	**ft_split_free(int j, char ***return_ptr)
{
	int	i;

	i = 0;
	while (i < j)
	{
		free((*return_ptr)[i]);
		i++;
	}
	free(*return_ptr);
	return (0);
}

void	init(int *i, int *len, int *j)
{
	*i = 0;
	*len = 0;
	*j = 0;
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		len;
	int		j;
	char	**return_ptr;

	init(&i, &len, &j);
	if (!s)
		return (0);
	return_ptr = (char **)malloc(sizeof(char *) * (word_num(s, c) + 1));
	if (!return_ptr)
		return (0);
	while (s[i])
	{
		if (!ft_split_helper(&s, &i, c, &len))
			break ;
		return_ptr[j] = ft_substr(s, i, len);
		if (!return_ptr[j])
			return (ft_split_free(j, &return_ptr));
		i += len;
		len = 0;
		j++;
	}
	return_ptr[j] = 0;
	return (return_ptr);
}
