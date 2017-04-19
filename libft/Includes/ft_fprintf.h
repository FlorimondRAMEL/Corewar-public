/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framel <framel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 17:33:17 by framel            #+#    #+#             */
/*   Updated: 2017/03/27 17:51:38 by framel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FPRINTF_H
# define FT_FPRINTF_H

# include <stdarg.h>
# include "libft.h"

typedef struct	s_printf
{
	int			ret;
	int			buff_size;
	char		*buff;
	int			is_percent_d;
	int			is_percent_s;
	int			is_percent_c;
	int			i;
}				t_printf;

int				ft_fprintf(int fd, const char *format, ...);
void			percent_d(t_printf *print, va_list pa);
void			percent_s(t_printf *print, va_list pa);
void			percent_c(t_printf *print, va_list pa);
void			percent_l(t_printf *print, va_list pa);

/*
** tools.c
*/

void			print_buff(t_printf *print, int *fd);
void			init_struct(t_printf *print);

#endif
