/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestrue <rdestrue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/15 22:46:47 by rdestrue          #+#    #+#             */
/*   Updated: 2016/01/21 22:39:23 by rdestrue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putnbr_recur_fd(int n, int fd)
{
	if (n <= -10)
		ft_putnbr_recur_fd(n / 10, fd);
	ft_putchar_fd(-(n % 10) + '0', fd);
}

void		ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
		ft_putchar_fd('-', fd);
	else
		n = -n;
	ft_putnbr_recur_fd(n, fd);
}
