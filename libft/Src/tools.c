/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framel <framel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 17:40:23 by framel            #+#    #+#             */
/*   Updated: 2017/03/27 17:40:37 by framel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

void	init_struct(t_printf *print)
{
	print->buff = NULL;
	print->buff_size = 0;
	print->ret = 0;
	print->is_percent_c = 0;
	print->is_percent_s = 0;
	print->is_percent_d = 0;
	print->i = 0;
}

void	print_buff(t_printf *print, int *fd)
{
	print->buff[print->i] = '\0';
	ft_putstr_fd(print->buff, *fd);
	free(print->buff);
}
