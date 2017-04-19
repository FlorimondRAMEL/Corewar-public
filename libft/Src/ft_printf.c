/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestrue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/31 18:01:56 by rdestrue          #+#    #+#             */
/*   Updated: 2016/08/16 21:20:34 by rdestrue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_reading_formatstr(const char **format, t_format *param, \
		intmax_t *cnt)
{
	while (**format != '\0' && **format != '%')
	{
		ft_putchar(**format);
		(*cnt)++;
		(*format)++;
	}
	if (**format == '%')
	{
		param->flg_md = 0;
		param->width = 0;
		param->prec = 0;
		param->format = 0;
		(*format)++;
		return (1);
	}
	return (0);
}

static int	ft_deal_arg(const char **format, t_format *param, va_list ap, \
		intmax_t *cnt)
{
	ft_flags(format, param);
	if (**format == '*' || ft_isdigit(**format))
		param->width = ft_field_width(format, param, ap);
	if (**format == '.')
		param->prec = ft_precision(format, param, ap);
	ft_modifiers(format, param);
	if (ft_specifier(format, param, ap, cnt) == -1)
		return (-1);
	else
		(*format)++;
	return (0);
}

int			ft_printf(const char *format, ...)
{
	va_list		ap;
	t_format	*param;
	intmax_t	cnt;
	int			test;

	param = malloc(sizeof(*param));
	if (param == NULL)
		return (-1);
	param->ref_flags = "#0-+ ";
	param->ref_spec = "bknpixXscdoufSCDOUF%";
	cnt = 0;
	ft_fcts_array();
	va_start(ap, format);
	test = 0;
	while (*format != '\0' && test == 0 && cnt != -1)
	{
		if (ft_reading_formatstr(&format, param, &cnt) == 0)
			test = 1;
		else if (ft_deal_arg(&format, param, ap, &cnt) == -1)
			cnt = -1;
	}
	va_end(ap);
	free(param);
	return (cnt);
}
