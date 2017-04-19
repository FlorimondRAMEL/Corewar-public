/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live_ld_st.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestrue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 17:52:27 by rdestrue          #+#    #+#             */
/*   Updated: 2017/03/28 12:26:45 by rdestrue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		ft_write_to_mem(t_env *env, short p2, int reg_val)
{
	if (p2 < 0)
		p2 = MEM_SIZE + p2 % MEM_SIZE;
	(*env).mem[p2 % MEM_SIZE] = (reg_val >> 24) & 0xFF;
	(*env).mem[(p2 + 1) % MEM_SIZE] = (reg_val >> 16) & 0xFF;
	(*env).mem[(p2 + 2) % MEM_SIZE] = (reg_val >> 8) & 0xFF;
	(*env).mem[(p2 + 3) % MEM_SIZE] = reg_val & 0xFF;
}

static void	ft_new_winner(t_data_prog **data_p, int param, int *j, t_env *env)
{
	if (param && param * (*env).zaz_opt == (*data_p)[*j].nb && \
			param * (*env).zaz_opt == (*data_p)[*j].parent)
	{
		(*env).current_winner = *j;
		if (!(*env).silent)
			ft_printf("Un processus dit que le joueur %d (%s) est en vie.\n"\
				, (*data_p)[*j].nb, (*data_p)[*j].name);
		*j = 0;
	}
}

int			do_live(t_data_prog **data_p, int i, t_env *env)
{
	int		param;
	int		j;

	param = ((*env).mem[((*data_p)[i].pc + 1) % MEM_SIZE] << 24) + \
			((*env).mem[((*data_p)[i].pc + 2) % MEM_SIZE] << 16) + \
			((*env).mem[((*data_p)[i].pc + 3) % MEM_SIZE] << 8) + \
			(*env).mem[((*data_p)[i].pc + 4) % MEM_SIZE];
	(*data_p)[i].last_live = (*env).cycle;
	(*env).live_counter += 1;
	if ((*env).verbose)
		ft_printf("Le proc. %d fait un LIVE (%d).\n", (*data_p)[i].nb, param);
	j = (*env).nb_usr - 1;
	while (j >= 0)
	{
		ft_new_winner(data_p, param, &j, env);
		j--;
	}
	(*data_p)[i].pc = ((*data_p)[i].pc + 5) % MEM_SIZE;
	return (0);
}

int			do_ld(t_data_prog **data_prog, int i, t_env *env)
{
	int				param1;
	unsigned char	reg2;
	unsigned char	octet_count;
	unsigned char	ocp;

	ocp = (*env).mem[((*data_prog)[i].pc + 1) % MEM_SIZE];
	octet_count = 2;
	if (ft_test(env, (*data_prog)[i].pc, ocp, 1) == 0)
	{
		param1 = retrieve_param(&(*data_prog)[i], env, &octet_count, PARAM_1);
		reg2 = (*env).mem[((*data_prog)[i].pc + octet_count) % MEM_SIZE] - 1;
		if (reg2 < 0 || reg2 >= REG_NUMBER)
			return (0);
		(*data_prog)[i].reg[reg2] = param1;
		(*data_prog)[i].carry = ((*data_prog)[i].reg[reg2] == 0) ? 1 : 0;
		if ((*env).verbose)
			ft_printf("Le processus %d fait un LOAD (%d -> r%hhu).\n", \
				(*data_prog)[i].nb, param1, reg2 + 1);
	}
	(*data_prog)[i].pc = ((*data_prog)[i].pc + 2 + ocp_value(ocp, 2, 4)) % \
		MEM_SIZE;
	return (0);
}

int			do_st(t_data_prog **data_prog, int i, t_env *env)
{
	unsigned char	r1;
	short			p2;
	unsigned char	ocp;

	ocp = (*env).mem[((*data_prog)[i].pc + 1) % MEM_SIZE];
	if (ft_test(env, (*data_prog)[i].pc, ocp, 2) == 0)
	{
		r1 = (*env).mem[((*data_prog)[i].pc + 2) % MEM_SIZE] - 1;
		p2 = (*env).mem[((*data_prog)[i].pc + 3) % MEM_SIZE];
		if (((ocp & 0x30) >> 4) == IND_CODE)
		{
			p2 = (p2 << 8) + (*env).mem[((*data_prog)[i].pc + 4) % MEM_SIZE];
			ft_write_to_mem(env, (int)((*data_prog)[i].pc + p2 % IDX_MOD), \
				(*data_prog)[i].reg[r1]);
		}
		else
			(*data_prog)[i].reg[p2 - 1] = (*data_prog)[i].reg[r1];
		if ((*env).verbose)
			ft_printf("Le processus %d fait un STORE (r%hhu -> %hd).\n", \
				(*data_prog)[i].nb, r1 + 1, p2);
	}
	(*data_prog)[i].pc = ((*data_prog)[i].pc + 2 + ocp_value(ocp, 2, 4)) % \
		MEM_SIZE;
	return (0);
}
