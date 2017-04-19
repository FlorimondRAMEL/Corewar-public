/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   percent_d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framel <framel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 17:39:30 by framel            #+#    #+#             */
/*   Updated: 2017/03/27 17:39:37 by framel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

void	percent_d(t_printf *print, va_list pa)
{
	char	*string;

	string = ft_ltoa(va_arg(pa, long));
	if (print->is_percent_d == 1)
	{
		ft_strcat(print->buff, string);
		print->i += ft_strlen(string);
	}
	else
		print->buff_size += ft_strlen(string);
	free(string);
}
