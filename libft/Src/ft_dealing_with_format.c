/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dealing_with_format.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestrue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/31 20:44:23 by rdestrue          #+#    #+#             */
/*   Updated: 2016/08/16 20:17:40 by rdestrue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_flags(const char **format, t_format *param)
{
	int	i;

	i = 0;
	while (param->ref_flags[i] != **format && param->ref_flags[i] != '\0')
		i++;
	if (param->ref_flags[i] == **format)
	{
		if (i == 0)
			param->flg_md = param->flg_md | DIESE;
		else if (i == 1)
			param->flg_md = param->flg_md | ZERO;
		else if (i == 2)
			param->flg_md = param->flg_md | MINUS;
		else if (i == 3)
			param->flg_md = param->flg_md | PLUS;
		else if (i == 4)
			param->flg_md = param->flg_md | SPACE;
		(*format)++;
		ft_flags(format, param);
	}
	return (0);
}

int		ft_field_width(const char **format, t_format *param, va_list ap)
{
	int field_width;

	if (**format == '*')
	{
		field_width = va_arg(ap, int);
		(*format)++;
		if (field_width < 0)
		{
			param->flg_md = param->flg_md | MINUS;
			field_width = -field_width;
		}
	}
	else
	{
		field_width = ft_atoi(*format);
		while (ft_isdigit(**format))
			(*format)++;
	}
	return (field_width);
}

int		ft_precision(const char **format, t_format *param, va_list ap)
{
	int precision;

	param->flg_md = param->flg_md | PREC;
	(*format)++;
	if (**format == '*')
	{
		precision = va_arg(ap, int);
		(*format)++;
		if (precision < 0)
		{
			precision = 0;
			param->flg_md = param->flg_md & ~(PREC);
		}
	}
	else
	{
		precision = ft_atoi(*format);
		while (ft_isdigit(**format))
			(*format)++;
	}
	return (precision);
}

int		ft_modifiers(const char **format, t_format *param)
{
	if (**format == 'h')
	{
		if ((*format)[1] == 'h')
			param->flg_md = param->flg_md | TWOH;
		else
			param->flg_md = param->flg_md | ONEH;
	}
	else if (**format == 'l')
	{
		if ((*format)[1] == 'l')
			param->flg_md = param->flg_md | TWOL;
		else
			param->flg_md = param->flg_md | ONEL;
	}
	else if (**format == 'j')
		param->flg_md = param->flg_md | ONEJ;
	else if (**format == 'z')
		param->flg_md = param->flg_md | ONEZ;
	if (param->flg_md >= TWOH)
		*format = (*format) + 2;
	else if (param->flg_md >= ONEH)
		(*format)++;
	return (0);
}

int		ft_specifier(const char **format, t_format *param, va_list ap, \
		intmax_t *cnt)
{
	int	i;

	i = 0;
	while (param->ref_spec[i] != **format && param->ref_spec[i] != '\0')
		i++;
	if (param->ref_spec[i] == **format && **format != '\0')
	{
		param->format = **format;
		if (i == 19)
		{
			if (ft_percent(param, cnt) != -1)
				return (0);
		}
		else
		{
			if (i > 12)
			{
				param->flg_md = param->flg_md | ONEL;
				i = i - 6;
			}
			if (g_ft_fcts_ptr[i](param, ap, cnt) != -1)
				return (0);
		}
	}
	return (-1);
}
