/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_byte.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudra <hboudra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 14:24:28 by hboudra           #+#    #+#             */
/*   Updated: 2017/03/29 15:36:00 by framel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	help(char **param, int *byte, char opcode)
{
	while (param && *param)
	{
		if (is_reg(*param))
			(*byte)++;
		else if (is_direct(*param))
		{
			if (opcode == ZJUMP || opcode == LDI
				|| opcode == STI || opcode == FORK
				|| opcode == LLDI || opcode == LFORK)
				(*byte) += 2;
			else
				(*byte) += 4;
		}
		else if (is_ind(*param))
			(*byte) += 2;
		param++;
	}
}

int			count_byte_inst(t_info *info)
{
	int		byte;
	char	**param;
	char	opcode;

	byte = 0;
	if (info && (opcode = info->opcode) > 0)
	{
		byte++;
		if (opcode != LIVE && opcode != ZJUMP && opcode != FORK)
			byte++;
		param = info->param;
		help(param, &byte, opcode);
	}
	if (info->opcode == LFORK)
		return (3);
	return (byte);
}
