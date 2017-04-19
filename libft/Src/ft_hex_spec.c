/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex_spec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestrue <rdestrue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/12 21:15:39 by rdestrue          #+#    #+#             */
/*   Updated: 2016/08/16 19:12:27 by rdestrue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_x(t_format *param, va_list ap, intmax_t *cnt)
{
	char	*str;
	char	c;

	str = ft_unsigned_nb(param, ap, 16);
	if (str != NULL && str[0] == '0')
	{
		param->flg_md = param->flg_md & ~(DIESE);
		if ((param->flg_md & PREC) == PREC && param->prec == 0)
			str[0] = '\0';
	}
	c = ((param->flg_md & DIESE) == DIESE ? 'x' : 'a');
	if (str != NULL)
		str = ft_nb_prec(str, param, c);
	if (str != NULL && c == 'x')
		str = ft_nb_diese_plus_space(str, c);
	if (str != NULL)
		str = ft_str_tolower(str);
	if (str == NULL)
		return (-1);
	if (ft_handle_str(param, str, cnt) == -1)
		return (-1);
	return (0);
}

int			ft_bigx(t_format *param, va_list ap, intmax_t *cnt)
{
	char	*str;
	char	c;

	str = ft_unsigned_nb(param, ap, 16);
	if (str != NULL && str[0] == '0')
	{
		param->flg_md = param->flg_md & ~(DIESE);
		if ((param->flg_md & PREC) == PREC && param->prec == 0)
			str[0] = '\0';
	}
	c = ((param->flg_md & DIESE) == DIESE ? 'X' : 'a');
	if (str != NULL)
		str = ft_nb_prec(str, param, c);
	if (str != NULL && c == 'X')
		str = ft_nb_diese_plus_space(str, c);
	if (str == NULL)
		return (-1);
	if (ft_handle_str(param, str, cnt) == -1)
		return (-1);
	return (0);
}

int			ft_p(t_format *param, va_list ap, intmax_t *cnt)
{
	char	*str;
	int		i;

	param->flg_md = param->flg_md | DIESE;
	param->flg_md = param->flg_md | ONEL;
	str = ft_unsigned_nb(param, ap, 16);
	if (str != NULL)
	{
		if (str[0] == '0' && (param->flg_md & PREC) == PREC && param->prec == 0)
			str[0] = '\0';
		str = ft_nb_prec(str, param, 'x');
		str = ft_nb_diese_plus_space(str, 'x');
	}
	else
		return (-1);
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] = str[i] + 32;
		i++;
	}
	if (ft_handle_str(param, str, cnt) == -1)
		return (-1);
	return (0);
}
