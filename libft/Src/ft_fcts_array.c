/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fcts_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestrue <rdestrue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/13 12:53:38 by rdestrue          #+#    #+#             */
/*   Updated: 2016/08/16 20:17:21 by rdestrue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_fcts_array(void)
{
	g_ft_fcts_ptr[0] = &ft_b;
	g_ft_fcts_ptr[1] = &ft_k;
	g_ft_fcts_ptr[2] = &ft_n;
	g_ft_fcts_ptr[3] = &ft_p;
	g_ft_fcts_ptr[4] = &ft_d;
	g_ft_fcts_ptr[5] = &ft_x;
	g_ft_fcts_ptr[6] = &ft_bigx;
	g_ft_fcts_ptr[7] = &ft_s;
	g_ft_fcts_ptr[8] = &ft_c;
	g_ft_fcts_ptr[9] = &ft_d;
	g_ft_fcts_ptr[10] = &ft_o;
	g_ft_fcts_ptr[11] = &ft_u;
	g_ft_fcts_ptr[12] = &ft_f;
}
