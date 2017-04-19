/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_param.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudra <hboudra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 15:32:41 by hboudra           #+#    #+#             */
/*   Updated: 2017/03/29 15:36:47 by framel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	w_param(int fd, t_info *info, t_glob glob)
{
	char	**param;
	int		i;

	param = info->param;
	i = 0;
	while (param && *param)
	{
		if (is_reg(*param))
			write_reg(fd, i, info);
		else if (is_direct(*param))
			write_dir(fd, i, info, glob);
		else if (is_ind(*param))
			write_ind(fd, i, info, glob);
		else
			error(BAD_ARGUMENT);
		i++;
		param++;
	}
}

static void	deal_param(int fd, t_info *info, t_glob glob)
{
	char	*opcode;
	char	*ocp;

	opcode = &info->opcode;
	ocp = (char*)&info->ocp;
	write(fd, opcode, 1);
	if (*opcode != LIVE && *opcode != ZJUMP && *opcode != FORK && \
		*opcode != LFORK)
		write(fd, ocp, 1);
	w_param(fd, info, glob);
}

void		write_param(int fd, t_glob glob)
{
	t_info	*info;

	info = glob.list;
	while (info)
	{
		deal_param(fd, info, glob);
		info = info->next;
	}
}
