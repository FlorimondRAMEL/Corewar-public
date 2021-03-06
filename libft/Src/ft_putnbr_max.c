/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_max.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestrue <rdestrue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/15 22:46:47 by rdestrue          #+#    #+#             */
/*   Updated: 2016/08/16 18:57:49 by rdestrue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putnbr_recur(intmax_t n)
{
	if (n <= -10)
		ft_putnbr_recur(n / 10);
	ft_putchar(-(n % 10) + '0');
}

void		ft_putnbr_max(intmax_t n)
{
	if (n < 0)
		ft_putchar('-');
	else
		n = -n;
	ft_putnbr_recur(n);
}
