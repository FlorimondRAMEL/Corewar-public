/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signed_spec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestrue <rdestrue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/12 21:15:39 by rdestrue          #+#    #+#             */
/*   Updated: 2016/08/16 19:10:28 by rdestrue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*ft_nb_diese_plus_space(char *str, char c)
{
	char	*new;
	int		len;

	len = (c == 'x' || c == 'X') ? ft_strlen(str) + 2 : ft_strlen(str) + 1;
	new = ft_strnew(len);
	if (new == NULL)
		return (new);
	if (c == '+' || c == ' ' || c == '-')
		new[0] = c;
	else if (c == 'x' || c == 'X' || c == 'o')
		new[0] = '0';
	if (c == 'x' || c == 'X')
		new[1] = c;
	if ((int)ft_strlcat(new, str, len + 1) != len)
	{
		free(new);
		return (NULL);
	}
	else
	{
		free(str);
		return (new);
	}
}

static char	*ft_neg(char *str, char *c)
{
	char	*new;
	char	*tmp;
	int		str_size;

	*c = '-';
	str_size = (int)ft_strlen(str);
	new = ft_strnew(str_size - 1);
	if (new == NULL)
		return (new);
	tmp = str + 1;
	if ((int)ft_strlcat(new, tmp, str_size) != str_size - 1)
	{
		free(new);
		return (NULL);
	}
	free(str);
	return (new);
}

static char	*ft_signed_nb(t_format *param, va_list ap, int base)
{
	char *str;

	if ((param->flg_md & ONEJ) == ONEJ)
		str = ft_itoa_base_max(va_arg(ap, intmax_t), base);
	else if ((param->flg_md & ONEZ) == ONEZ)
		str = ft_itoa_base_max(va_arg(ap, intmax_t), base);
	else if ((param->flg_md & TWOL) == TWOL)
		str = ft_itoa_base_max(va_arg(ap, long long), base);
	else if ((param->flg_md & ONEL) == ONEL)
		str = ft_itoa_base_max(va_arg(ap, long), base);
	else if ((param->flg_md & ONEH) == ONEH)
		str = ft_itoa_base((short)va_arg(ap, int), base);
	else if ((param->flg_md & TWOH) == TWOH)
		str = ft_itoa_base((char)va_arg(ap, int), base);
	else
		str = ft_itoa_base(va_arg(ap, int), base);
	return (str);
}

int			ft_d(t_format *param, va_list ap, intmax_t *cnt)
{
	char	*str;
	char	c;

	c = 'a';
	str = ft_signed_nb(param, ap, 10);
	if (str != NULL && str[0] != '-' && (param->flg_md & PLUS) == PLUS)
		c = '+';
	else if (str != NULL && str[0] != '-' && (param->flg_md & SPACE) == SPACE)
		c = ' ';
	else if (str != NULL && str[0] == '-')
		str = ft_neg(str, &c);
	if ((param->flg_md & PREC) == PREC && param->prec == 0 && str != NULL \
			&& str[0] == '0')
		str[0] = '\0';
	else if (str != NULL)
		str = ft_nb_prec(str, param, c);
	if (str != NULL && str[0] != '\0' && (c == '+' || c == ' ' || c == '-'))
		str = ft_nb_diese_plus_space(str, c);
	if (str == NULL || ft_handle_str(param, str, cnt) == -1)
		return (-1);
	return (0);
}

int			ft_f(t_format *param, va_list ap, intmax_t *cnt)
{
	char	*str;
	char	c;

	c = 'a';
	if ((param->flg_md & PREC) == 0)
		param->prec = 6;
	param->flg_md = param->flg_md | PREC;
	str = ft_ftoa_base(va_arg(ap, double), 10, param->prec, param->format);
	if (str != NULL && str[0] != '-' && (param->flg_md & PLUS) == PLUS)
		c = '+';
	else if (str != NULL && str[0] != '-' && (param->flg_md & SPACE) == SPACE)
		c = ' ';
	else if (str != NULL && str[0] == '-')
		str = ft_neg(str, &c);
	if (str != NULL && ft_isdigit(str[0]))
		str = ft_nb_prec(str, param, c);
	if (str != NULL && str[0] != '\0' && (c == '+' || c == ' ' || c == '-'))
		str = ft_nb_diese_plus_space(str, c);
	if (str == NULL || ft_handle_str(param, str, cnt) == -1)
		return (-1);
	return (0);
}
