/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   percent_c.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framel <framel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 17:39:01 by framel            #+#    #+#             */
/*   Updated: 2017/03/27 17:39:12 by framel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

void	percent_c(t_printf *print, va_list pa)
{
	char	c;

	c = va_arg(pa, int);
	if (print->is_percent_c == 1)
	{
		print->buff[print->i] = c;
		++print->i;
	}
	else
		++print->buff_size;
}
