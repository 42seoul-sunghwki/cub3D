/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 21:41:12 by minsepar          #+#    #+#             */
/*   Updated: 2024/03/04 21:31:28 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif
# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

typedef struct s_fd_node
{
	int					fd;
	size_t				cursor;
	size_t				word_size;
	struct s_fd_node	*next;
	size_t				size;
	char				*str;
}	t_fd_node;

void			*ft_read_line_helper(t_fd_node *cur, t_fd_node **front,
					ssize_t *ret);
void			*fd_deletenode(t_fd_node **front, int fd);
char			*get_next_line(int fd);
char			*ft_substr(char const *s, unsigned int start, size_t len);
t_fd_node		*fd_newnode(int fd);
t_fd_node		*fd_addnode(t_fd_node **front, int fd);
void			*ft_free(void **zmem1, void *mem2, void *mem3);
#endif
