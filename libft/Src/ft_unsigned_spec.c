/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsigned_spec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestrue <rdestrue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/12 21:15:39 by rdestrue          #+#    #+#             */
/*   Updated: 2016/08/12 00:27:50 by rdestrue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_unsigned_nb(t_format *param, va_list ap, int base)
{
	char *str;

	if ((param->flg_md & ONEJ) == ONEJ)
		str = ft_itoa_base_umax(va_arg(ap, uintmax_t), base);
	else if ((param->flg_md & ONEZ) == ONEZ)
		str = ft_itoa_base_umax(va_arg(ap, size_t), base);
	else if ((param->flg_md & TWOL) == TWOL)
		str = ft_itoa_base_umax(va_arg(ap, unsigned long long), base);
	else if ((param->flg_md & ONEL) == ONEL)
		str = ft_itoa_base_umax(va_arg(ap, unsigned long), base);
	else if ((param->flg_md & ONEH) == ONEH)
		str = ft_itoa_base_u((unsigned short)va_arg(ap, unsigned int), base);
	else if ((param->flg_md & TWOH) == TWOH)
		str = ft_itoa_base_u((unsigned char)va_arg(ap, unsigned int), base);
	else
		str = ft_itoa_base_u(va_arg(ap, unsigned int), base);
	return (str);
}

int		ft_u(t_format *param, va_list ap, intmax_t *cnt)
{
	char *str;

	str = ft_unsigned_nb(param, ap, 10);
	if ((param->flg_md & PREC) == PREC && param->prec == 0 && str != NULL && \
			str[0] == '0')
		str[0] = '\0';
	else if (str != NULL)
		str = ft_nb_prec(str, param, 'a');
	if (str == NULL || ft_handle_str(param, str, cnt) == -1)
		return (-1);
	return (0);
}

int		ft_o(t_format *param, va_list ap, intmax_t *cnt)
{
	char	*str;
	char	c;

	str = ft_unsigned_nb(param, ap, 8);
	c = ((param->flg_md & DIESE) == DIESE ? 'o' : 'a');
	if ((param->flg_md & PREC) == PREC && param->prec == 0 && str != NULL && \
			str[0] == '0')
		str[0] = '\0';
	else if (str != NULL)
		str = ft_nb_prec(str, param, c);
	if (str != NULL && str[0] != '0' && c == 'o')
		str = ft_nb_diese_plus_space(str, c);
	if (str == NULL || ft_handle_str(param, str, cnt) == -1)
		return (-1);
	return (0);
}

int		ft_b(t_format *param, va_list ap, intmax_t *cnt)
{
	char	*str;

	str = ft_unsigned_nb(param, ap, 2);
	if ((param->flg_md & PREC) == PREC && param->prec == 0 && str != NULL && \
			ft_strlen(str) == 1 && str[0] == '0')
		str[0] = '\0';
	else if (str != NULL)
		str = ft_nb_prec(str, param, 'a');
	if (str == NULL || ft_handle_str(param, str, cnt) == -1)
		return (-1);
	return (0);
}
