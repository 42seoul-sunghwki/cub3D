/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 21:40:54 by minsepar          #+#    #+#             */
/*   Updated: 2023/10/23 19:03:50 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

t_fd_node	*fd_newnode(int fd)
{
	t_fd_node	*new_node;

	new_node = (t_fd_node *)malloc(sizeof(t_fd_node));
	if (!new_node)
		return (0);
	new_node->str = (char *)malloc((size_t)BUFFER_SIZE + 1);
	if (!new_node->str)
	{
		free(new_node);
		return (0);
	}
	new_node->str[0] = 0;
	new_node->size = BUFFER_SIZE;
	new_node->cursor = 0;
	new_node->word_size = 0;
	new_node->fd = fd;
	new_node->next = 0;
	return (new_node);
}

t_fd_node	*fd_addnode(t_fd_node **front, int fd)
{
	t_fd_node	*new_node;
	t_fd_node	*cur;

	cur = *front;
	new_node = fd_newnode(fd);
	if (!new_node)
		return (0);
	if (!*front || (*front)->fd > fd)
	{
		*front = new_node;
		(*front)->next = cur;
	}
	else
	{
		while (cur->next && cur->next->fd < fd)
			cur = cur->next;
		new_node->next = cur->next;
		cur->next = new_node;
	}
	return (new_node);
}

char	*read_return(t_fd_node *cur, t_fd_node **front)
{
	char	*temp;
	char	*save_str;

	if (cur->str[cur->cursor] == '\n')
		cur->cursor++;
	temp = ft_substr(cur->str, 0, cur->cursor);
	save_str = ft_substr(cur->str, cur->cursor, cur->word_size - cur->cursor);
	if (!temp || !save_str)
		if (!ft_free(0, temp, save_str))
			return (fd_deletenode(front, cur->fd));
	cur->size = cur->word_size - cur->cursor;
	cur->word_size = cur->size;
	cur->cursor = 0;
	free(cur->str);
	cur->str = save_str;
	return (temp);
}

char	*ft_read_line(int fd, t_fd_node *cur, t_fd_node **front)
{
	ssize_t	ret;

	while (1)
	{
		if (!ft_read_line_helper(cur, front, &ret))
			return (0);
		cur->word_size += ret;
		cur->str[cur->word_size] = 0;
		while (cur->str[cur->cursor] && cur->str[cur->cursor] != '\n')
			cur->cursor++;
		if ((cur->str[cur->cursor] == '\n') || (cur->cursor > 0 && ret == 0))
			return (read_return(cur, front));
		else if (cur->word_size == 0 && ret == 0)
			return (fd_deletenode(front, fd));
	}
}

char	*get_next_line(int fd)
{
	static t_fd_node	*front = 0;
	t_fd_node			*cur;
	char				*return_str;

	cur = front;
	while (cur && cur->fd < fd)
		cur = cur->next;
	if (!cur || cur->fd != fd)
		cur = fd_addnode(&front, fd);
	if (!cur)
		return (0);
	return_str = ft_read_line(fd, cur, &front);
	return (return_str);
}
