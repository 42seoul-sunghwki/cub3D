/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 14:02:06 by minsepar          #+#    #+#             */
/*   Updated: 2023/10/09 12:10:26 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*free_str(char **str)
{
	free(*str);
	return (0);
}

static t_list	*free_list(t_list *start, void (*del)(void *))
{
	ft_lstclear(&start, del);
	return (0);
}

static t_list	*free_list_str(t_list *start, void (*del)(void *), char **str)
{
	ft_lstclear(&start, del);
	del(*str);
	return (0);
}

static int	ft_lstmap_helper(t_list **lst, char **str, t_list **start,
		void *(*f)(void *))
{
	*str = f((*lst)->content);
	if (!(*str))
		return (0);
	*start = ft_lstnew(*str);
	if (!(*start))
	{
		if (!free_str(str))
			return (0);
	}
	return (1);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*start;
	t_list	*cur;
	t_list	*return_cur;
	char	*str;

	if (!lst || !f || !del)
		return (0);
	if (!ft_lstmap_helper(&lst, &str, &start, f))
		return (0);
	cur = lst;
	return_cur = start;
	while (cur->next)
	{
		str = f(cur->next->content);
		if (!str)
			return (free_list(start, del));
		return_cur->next = ft_lstnew(str);
		if (!return_cur->next)
			return (free_list_str(start, del, &str));
		cur = cur->next;
		return_cur = return_cur->next;
	}
	return (start);
}
