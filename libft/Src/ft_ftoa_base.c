/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestrue <rdestrue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/07 19:31:01 by rdestrue          #+#    #+#             */
/*   Updated: 2016/08/16 18:57:15 by rdestrue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

static char	*ft_inf_nan(double nb, char lcase)
{
	char	*str;

	str = ft_strnew(4);
	if (str != NULL && nb == 1.0 / 0)
	{
		if (lcase == 'f')
			ft_strlcat(str, "inf", 4);
		else
			ft_strlcat(str, "INF", 4);
	}
	else if (str != NULL && nb == -1.0 / 0)
	{
		if (lcase == 'f')
			ft_strlcat(str, "-inf", 5);
		else
			ft_strlcat(str, "-INF", 5);
	}
	else if (str != NULL && !(nb == nb))
	{
		if (lcase == 'f')
			ft_strlcat(str, "nan", 4);
		else
			ft_strlcat(str, "NAN", 4);
	}
	return (str);
}

static int	ft_decimal(double nb, int base, int nbdec, char *str)
{
	int					i;
	int					int_size;
	unsigned long long	decimal;
	char				*tmp;

	int_size = ft_strlen(str);
	str[int_size] = '.';
	if (nb < 0)
		nb = -nb;
	decimal = (unsigned long long)(((nb + 5.0 / (ft_power_max(10, nbdec + 1))) \
				- (long long)nb) * ft_power_max(10, nbdec));
	tmp = ft_itoa_base_umax(decimal, base);
	if (tmp == NULL)
		return (-1);
	i = int_size + nbdec - ft_strlen(tmp);
	if ((int)ft_strlen(tmp) != nbdec)
		while (i > int_size)
		{
			str[i] = '0';
			i--;
		}
	if ((int)ft_strlcat(str, tmp, int_size + nbdec + 2) != int_size + nbdec + 1)
		return (-1);
	free(tmp);
	return (0);
}

static char	*ft_integer(double nb, int base, int nbdec)
{
	char				*str;

	if (nbdec == 0)
	{
		if (nb >= 0)
			str = ft_itoa_base_max((long long)(nb + 0.5), base);
		else
			str = ft_itoa_base_max((long long)(nb - 0.5), base);
	}
	else
		str = ft_itoa_base_max((long long)nb, base);
	return (str);
}

char		*ft_ftoa_base(double nb, int base, int nbdec, char lcase)
{
	int					int_size;
	char				*tmp;
	char				*str;

	if (nb == 1.0 / 0 || nb == -1.0 / 0 || !(nb == nb))
	{
		str = ft_inf_nan(nb, lcase);
		return (str);
	}
	if (nb > LLONG_MAX || nb < LLONG_MIN || nbdec >= 18 || nbdec < 0)
		return (NULL);
	tmp = ft_integer(nb, base, nbdec);
	if (tmp == NULL)
		return (NULL);
	int_size = ft_strlen(tmp);
	str = ft_strnew(int_size + nbdec);
	if (str == NULL || (int)ft_strlcat(str, tmp, int_size + 1) != int_size)
		return (NULL);
	free(tmp);
	if (ft_decimal(nb, base, nbdec, str) == -1)
		return (NULL);
	return (str);
}
