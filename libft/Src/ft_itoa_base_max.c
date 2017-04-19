/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base_max.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestrue <rdestrue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/06 12:11:58 by rdestrue          #+#    #+#             */
/*   Updated: 2016/08/16 19:00:08 by rdestrue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_nblen_base(intmax_t nb, int base, int *len)
{
	if (nb < -(base - 1))
	{
		nb = nb / base;
		(*len)++;
		ft_nblen_base(nb, base, len);
	}
	else
		(*len)++;
}

static void	ft_convert(intmax_t nb, int base, char *str_nb, int len)
{
	char	*str_base;

	str_base = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	if (nb < -(base - 1))
	{
		str_nb[len - 1] = str_base[-(nb % base)];
		len--;
		nb = nb / base;
		ft_convert(nb, base, str_nb, len);
	}
	else
		str_nb[len - 1] = str_base[-nb];
}

char		*ft_itoa_base_max(intmax_t nb, int base)
{
	int		len;
	int		neg;
	char	*str_nb;

	if (base < 2 || base > 36)
		return (NULL);
	neg = 0;
	if (nb < 0)
		neg = 1;
	else
		nb = -nb;
	len = 0;
	ft_nblen_base(nb, base, &len);
	if (neg == 1)
		len++;
	str_nb = ft_strnew(len);
	if (neg == 1)
		str_nb[0] = '-';
	ft_convert(nb, base, str_nb, len);
	return (str_nb);
}
