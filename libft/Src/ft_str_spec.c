/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_spec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestrue <rdestrue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/12 21:15:39 by rdestrue          #+#    #+#             */
/*   Updated: 2016/08/16 19:12:40 by rdestrue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_handle_str(t_format *param, char *str, intmax_t *cnt)
{
	int str_size;

	str_size = (int)ft_strlen(str);
	if (param->width > str_size || ((ft_strcmp(str, "(null)") == 0 || \
			param->format == 's') && (param->flg_md & PREC) == PREC && \
			param->prec < str_size))
		str = ft_wider_field(str, param);
	if (str == NULL)
		return (-1);
	ft_putstr(str);
	*cnt = *cnt + (int)ft_strlen(str);
	if (!((param->format == 's' || ft_strcmp(str, "(null)") == 0) && \
			param->width <= str_size && ((param->flg_md & PREC) == 0 || \
			param->prec >= str_size)))
		free(str);
	return (0);
}

static int	ft_bigs_chars(t_format *param, wchar_t *wstr, char *str, int i)
{
	char	*tmp;
	int		newlen;

	tmp = ft_wcharconv(wstr[i]);
	if (tmp == NULL)
		return (-1);
	newlen = (int)ft_strlen(str) + (int)ft_strlen(tmp);
	if ((param->flg_md & PREC) == PREC && newlen > param->prec)
	{
		free(tmp);
		return (1);
	}
	else
	{
		if ((int)ft_strlcat(str, tmp, newlen + 1) != newlen)
		{
			free(tmp);
			return (-1);
		}
		else
			free(tmp);
	}
	return (0);
}

static char	*ft_bigs_handling(t_format *param, wchar_t *wstr, int wlen)
{
	char	*str;
	int		i;
	int		feedback;

	str = ft_strnew(4 * wlen);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (wstr[i])
	{
		feedback = ft_bigs_chars(param, wstr, str, i);
		if (feedback == -1)
			return (NULL);
		else if (feedback == 1)
			return (str);
		i++;
	}
	return (str);
}

int			ft_s(t_format *param, va_list ap, intmax_t *cnt)
{
	char	*str;
	wchar_t	*wstr;
	int		wlen;

	wstr = NULL;
	if ((param->flg_md & ONEL) == ONEL)
	{
		wstr = va_arg(ap, wchar_t *);
		if (wstr == NULL)
			str = "(null)";
		else
		{
			wlen = (int)ft_wstrlen(wstr);
			str = ft_bigs_handling(param, wstr, wlen);
		}
	}
	else
	{
		str = va_arg(ap, char *);
		if (str == NULL)
			str = "(null)";
	}
	if (str == NULL || ft_handle_str(param, str, cnt) == -1)
		return (-1);
	return (0);
}

int			ft_n(t_format *param, va_list ap, intmax_t *cnt)
{
	if ((param->flg_md & ONEJ) == ONEJ)
		*(va_arg(ap, intmax_t *)) = *cnt;
	else if ((param->flg_md & ONEZ) == ONEZ)
		*(va_arg(ap, intmax_t *)) = *cnt;
	else if ((param->flg_md & TWOL) == TWOL)
		*(va_arg(ap, long long *)) = *cnt;
	else if ((param->flg_md & ONEL) == ONEL)
		*(va_arg(ap, long *)) = *cnt;
	else if ((param->flg_md & ONEH) == ONEH)
		*(va_arg(ap, short *)) = *cnt;
	else if ((param->flg_md & TWOH) == TWOH)
		*(va_arg(ap, char *)) = *cnt;
	else
		*(va_arg(ap, int *)) = *cnt;
	return (0);
}
