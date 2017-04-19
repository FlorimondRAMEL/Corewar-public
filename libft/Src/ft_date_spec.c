/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_date_spec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestrue <rdestrue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/12 21:15:39 by rdestrue          #+#    #+#             */
/*   Updated: 2016/08/16 19:06:38 by rdestrue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_k_date1(char *str, va_list ap)
{
	char	*tmp;
	int		nb;

	nb = va_arg(ap, int);
	if (nb >= 1583 && nb <= 9999)
	{
		ft_strlcat(str, ft_itoa(nb), 5);
		str[4] = '-';
	}
	else
		return (-1);
	nb = va_arg(ap, int);
	if (nb >= 1 && nb <= 12)
	{
		tmp = ft_itoa(nb);
		if (ft_strlen(tmp) == 1)
			str[5] = '0';
		ft_strlcat(str, tmp, 8);
		str[7] = '-';
		free(tmp);
	}
	else
		return (-1);
	return (0);
}

static int	ft_k_date2(char *str, va_list ap)
{
	char	*tmp;
	int		nb;

	nb = va_arg(ap, int);
	if (nb >= 1 && nb <= 31)
	{
		tmp = ft_itoa(nb);
		if (ft_strlen(tmp) == 1)
			str[8] = '0';
		ft_strlcat(str, tmp, 11);
		free(tmp);
	}
	else
		return (-1);
	return (0);
}

static int	ft_k_hour1(char *str, va_list ap)
{
	char	*tmp;
	int		nb;

	str[10] = 'T';
	nb = va_arg(ap, int);
	if (nb >= 0 && nb <= 23)
	{
		tmp = ft_itoa(nb);
		if (ft_strlen(tmp) == 1)
			str[11] = '0';
		ft_strlcat(str, tmp, 14);
		str[13] = ':';
		free(tmp);
	}
	else
		return (-1);
	return (0);
}

static int	ft_k_hour2(char *str, va_list ap)
{
	char	*tmp;
	int		nb;

	nb = va_arg(ap, int);
	if (nb >= 0 && nb <= 59)
	{
		tmp = ft_itoa(nb);
		if (ft_strlen(tmp) == 1)
			str[14] = '0';
		ft_strlcat(str, tmp, 17);
		free(tmp);
	}
	else
		return (-1);
	return (0);
}

int			ft_k(t_format *param, va_list ap, intmax_t *cnt)
{
	char	*str;

	if ((param->flg_md & ONEL) == ONEL)
		str = ft_strnew(22);
	else if ((param->flg_md & ONEZ) == ONEZ)
		str = ft_strnew(17);
	else
		str = ft_strnew(10);
	if (str == NULL)
		return (-1);
	if (ft_k_date1(str, ap) == -1 || ft_k_date2(str, ap) == -1)
		return (-1);
	if ((param->flg_md & ONEL) == ONEL || (param->flg_md & ONEZ) == ONEZ)
		if (ft_k_hour1(str, ap) == -1 || ft_k_hour2(str, ap) == -1)
			return (-1);
	if ((param->flg_md & ONEL) == ONEL)
	{
		if (ft_k_hour_suffixe(str, ap) == -1)
			return (-1);
	}
	else
		str[16] = 'Z';
	if (ft_handle_str(param, str, cnt) == -1)
		return (-1);
	return (0);
}
