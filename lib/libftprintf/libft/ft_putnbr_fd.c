/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 12:16:05 by minsepar          #+#    #+#             */
/*   Updated: 2023/10/07 17:33:56 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putnbr_recur(int len, long n, int fd)
{
	char	c;

	c = n % 10 + '0';
	if (len > 1)
		ft_putnbr_recur(len - 1, n /= 10, fd);
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	int		len;
	long	temp;
	long	temp_2;

	temp = n;
	len = 0;
	if (temp < 0)
	{
		write(fd, "-", 1);
		temp *= -1;
	}
	if (n == 0)
		len = 1;
	temp_2 = temp;
	while (temp > 0)
	{
		len++;
		temp /= 10;
	}
	ft_putnbr_recur(len, temp_2, fd);
}
