/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_spec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestrue <rdestrue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/12 21:15:39 by rdestrue          #+#    #+#             */
/*   Updated: 2016/08/16 19:12:09 by rdestrue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_k_hour_suffixe(char *str, va_list ap)
{
	char	*tmp;
	int		nb;

	nb = va_arg(ap, int);
	if (nb >= -12 && nb <= 12)
	{
		tmp = ft_itoa(nb);
		if (tmp[0] == '-')
			str[16] = '-';
		else
			str[16] = '+';
		if (ft_strlen(tmp) == 1 || (ft_strlen(tmp) == 2 && tmp[0] == '-'))
			str[17] = '0';
		if (tmp[0] == '-')
			ft_strlcat(str, &tmp[1], 20);
		else
			ft_strlcat(str, tmp, 20);
		str[19] = ':';
		str[20] = '0';
		str[21] = '0';
		free(tmp);
	}
	else
		return (-1);
	return (0);
}

static int	ft_c_null(t_format *param, intmax_t *cnt, char *str)
{
	param->width = param->width - 1;
	if (param->width == 0)
		ft_putchar('\0');
	else if ((param->flg_md & MINUS) == MINUS)
	{
		ft_putchar('\0');
		if (ft_handle_str(param, str, cnt) == -1)
			return (-1);
	}
	else
	{
		if (ft_handle_str(param, str, cnt) == -1)
			return (-1);
		ft_putchar('\0');
	}
	(*cnt)++;
	return (0);
}

int			ft_c(t_format *param, va_list ap, intmax_t *cnt)
{
	char	*str;
	int		i;

	i = va_arg(ap, int);
	if ((param->flg_md & ONEL) == ONEL && i > 127)
		str = ft_wcharconv((wchar_t)i);
	else
	{
		str = ft_strnew(1);
		if (str != NULL)
			str[0] = (unsigned char)i;
		if (str != NULL && str[0] == '\0')
			return (ft_c_null(param, cnt, str));
	}
	if (str == NULL || ft_handle_str(param, str, cnt) == -1)
		return (-1);
	return (0);
}

int			ft_percent(t_format *param, intmax_t *cnt)
{
	char *str;

	str = ft_strnew(1);
	if (str == NULL)
		return (-1);
	str[0] = '%';
	if (ft_handle_str(param, str, cnt) == -1)
		return (-1);
	return (0);
}
