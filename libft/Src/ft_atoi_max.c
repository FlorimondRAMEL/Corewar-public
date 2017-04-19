/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_max.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestrue <rdestrue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/12 23:38:55 by rdestrue          #+#    #+#             */
/*   Updated: 2016/11/01 13:07:03 by rdestrue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

intmax_t	ft_atoi_max(const char *str)
{
	int			i;
	int			neg;
	intmax_t	nb;

	i = 0;
	nb = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\f'
			|| str[i] == '\r' || str[i] == '\v')
		i++;
	neg = 0;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		neg = 1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + str[i] - '0';
		i++;
	}
	if (neg == 1)
		nb = -nb;
	return (nb);
}
