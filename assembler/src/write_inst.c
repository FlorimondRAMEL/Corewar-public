/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_inst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudra <hboudra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 14:18:11 by hboudra           #+#    #+#             */
/*   Updated: 2017/03/23 21:49:49 by hboudra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	write_nb_inst(t_info *info, int fd)
{
	long	i;

	i = 0;
	while (info)
	{
		i += count_byte_inst(info);
		info = info->next;
	}
	i = invert_8(i);
	write(fd, (char*)&i, sizeof(long));
}
