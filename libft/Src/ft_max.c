/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_max.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestrue <rdestrue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/11 19:10:16 by rdestrue          #+#    #+#             */
/*   Updated: 2016/09/11 19:52:34 by rdestrue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_max(int nb, ...)
{
	int		max;
	int		tmp;
	va_list	ap;

	max = 0;
	tmp = 0;
	if (nb > 0)
	{
		va_start(ap, nb);
		max = va_arg(ap, int);
		nb--;
		while (nb)
		{
			tmp = va_arg(ap, int);
			if (tmp > max)
				max = tmp;
			nb--;
		}
		va_end(ap);
		return (max);
	}
	return (0);
}
