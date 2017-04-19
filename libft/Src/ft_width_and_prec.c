/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_width_and_prec.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestrue <rdestrue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/16 12:40:07 by rdestrue          #+#    #+#             */
/*   Updated: 2016/08/16 19:11:37 by rdestrue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <string.h>

static int	ft_width_minus(char *str, char *new, int new_size, int str_size)
{
	int	i;

	if ((int)ft_strlcat(new, str, str_size + 1) != (int)ft_strlen(str))
	{
		free(new);
		return (-1);
	}
	i = str_size;
	while (i < new_size)
	{
		new[i] = ' ';
		i++;
	}
	return (0);
}

static char	*ft_width(char *str, t_format *param, int new_size, int str_size)
{
	char	*new;
	int		i;

	new = ft_strnew(new_size);
	if (new != NULL && (param->flg_md & MINUS) == MINUS)
		if (ft_width_minus(str, new, new_size, str_size) == -1)
			return (NULL);
	if (new != NULL && (param->flg_md & MINUS) != MINUS)
	{
		i = 0;
		while (i < new_size - str_size)
		{
			new[i] = ((param->flg_md & ZERO) == ZERO && \
					ft_strchr("sScC%", param->format) != NULL) ? '0' : ' ';
			i++;
		}
		if ((int)ft_strlcat(new, str, new_size + 1) != new_size + \
				(int)ft_strlen(str) - str_size)
		{
			free(new);
			return (NULL);
		}
	}
	return (new);
}

char		*ft_wider_field(char *str, t_format *param)
{
	int		str_size;
	int		new_size;
	char	*new;

	if ((param->format != 's' && param->format != 'S') || param->width > \
			(int)ft_strlen(str) || ((param->flg_md & PREC) == PREC && \
			param->width > param->prec))
		new_size = param->width;
	else if ((param->flg_md & PREC) == PREC && param->prec < \
			(int)ft_strlen(str))
		new_size = param->prec;
	else
		return (str);
	if (param->format != 's' && param->format != 'S')
		str_size = (int)ft_strlen(str);
	else
		str_size = (((param->flg_md & PREC) == PREC) && (param->prec < \
				(int)ft_strlen(str))) ? param->prec : (int)ft_strlen(str);
	new = ft_width(str, param, new_size, str_size);
	if (!(param->format == 's' || ft_strcmp(str, "(null)") == 0))
		free(str);
	return (new);
}

static	int	ft_nb_newsize(t_format *param, char c, int str_size)
{
	int		new_size;

	if ((param->flg_md & PREC) == PREC && param->prec > str_size)
		new_size = param->prec;
	else if (param->width > str_size && (param->flg_md & ZERO) == ZERO \
			&& (param->flg_md & MINUS) == 0 && ((param->flg_md & \
			MINUS) == 0 || param->format == 'f' || param->format == 'F'))
	{
		if (c == 'x' || c == 'X')
			new_size = param->width - 2;
		else if (c == '+' || c == ' ' || c == '-')
			new_size = param->width - 1;
		else
			new_size = param->width;
	}
	else
		new_size = -1;
	return (new_size);
}

char		*ft_nb_prec(char *str, t_format *param, char c)
{
	char	*new;
	int		new_size;
	int		str_size;
	int		i;

	str_size = (int)ft_strlen(str);
	new_size = ft_nb_newsize(param, c, str_size);
	if (new_size == -1)
		return (str);
	new = ft_strnew(new_size);
	if (new == NULL)
		return (new);
	i = 0;
	while (i < new_size - str_size)
	{
		new[i] = '0';
		i++;
	}
	if ((int)ft_strlcat(new, str, new_size + 1) != new_size)
	{
		free(new);
		return (NULL);
	}
	free(str);
	return (new);
}
