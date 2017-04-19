/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_min.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestrue <rdestrue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/11 19:10:16 by rdestrue          #+#    #+#             */
/*   Updated: 2016/09/11 19:47:53 by rdestrue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_min(int nb, ...)
{
	int		min;
	int		tmp;
	va_list	ap;

	min = 0;
	tmp = 0;
	if (nb > 0)
	{
		va_start(ap, nb);
		min = va_arg(ap, int);
		nb--;
		while (nb)
		{
			tmp = va_arg(ap, int);
			if (tmp < min)
				min = tmp;
			nb--;
		}
		va_end(ap);
		return (min);
	}
	return (0);
}
