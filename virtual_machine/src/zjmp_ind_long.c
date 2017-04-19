/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp_ind_long.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestrue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 17:52:27 by rdestrue          #+#    #+#             */
/*   Updated: 2017/03/28 13:18:46 by rdestrue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		do_zjmp(t_data_prog **data_prog, int i, t_env *env)
{
	short	ind;

	if ((*data_prog)[i].carry == 1)
	{
		ind = (*env).mem[((*data_prog)[i].pc + 1) % MEM_SIZE];
		ind = (ind << 8) + (*env).mem[((*data_prog)[i].pc + 2) % MEM_SIZE];
		if ((*env).verbose)
			ft_printf("Le processus %d fait un JUMP de %hd.\n", \
				(*data_prog)[i].nb, ind % IDX_MOD);
		ind = ((*data_prog)[i].pc + ind % IDX_MOD);
		if (ind < 0)
			ind = MEM_SIZE + ind % MEM_SIZE;
		(*data_prog)[i].pc = ind % MEM_SIZE;
	}
	else
	{
		if ((*env).verbose)
			ft_printf("Le processus %d RATE un JUMP !\n", (*data_prog)[i].nb);
		(*data_prog)[i].pc = ((*data_prog)[i].pc + 3) % MEM_SIZE;
	}
	return (0);
}

int		do_ldi(t_data_prog **d_p, int i, t_env *env)
{
	int				i1;
	int				i2;
	unsigned char	r3;
	unsigned char	o_cnt;
	unsigned char	ocp;

	ocp = (*env).mem[((*d_p)[i].pc + 1) % MEM_SIZE];
	o_cnt = 2;
	if (ft_test(env, (*d_p)[i].pc, ocp, 9) == 0)
	{
		i1 = ((ocp & PARAM_1) >> 6 == DIR_CODE) ? \
			retrieve_dir_index(&(*d_p)[i], env, &o_cnt, PARAM_1) : \
			retrieve_param(&(*d_p)[i], env, &o_cnt, PARAM_1);
		i2 = ((ocp & PARAM_2) >> 4 == DIR_CODE) ? \
			retrieve_dir_index(&(*d_p)[i], env, &o_cnt, PARAM_2) : \
			retrieve_param(&(*d_p)[i], env, &o_cnt, PARAM_2);
		r3 = (*env).mem[((*d_p)[i].pc + o_cnt) % MEM_SIZE] - 1;
		(*d_p)[i].reg[r3] = retrieve_ind_val(&(*d_p)[i], env, \
			(i1 + i2) % IDX_MOD);
		if ((*env).verbose)
			ft_printf("Le proc. %d fait un LDI (%d + %d -> r%hhu).\n", \
				(*d_p)[i].nb, i1, i2, r3 + 1);
	}
	(*d_p)[i].pc = ((*d_p)[i].pc + 2 + ocp_value(ocp, 3, 2)) % MEM_SIZE;
	return (0);
}

int		do_sti(t_data_prog **data_p, int i, t_env *env)
{
	unsigned char	r1;
	int				ind2;
	int				ind3;
	unsigned char	octet_count;
	unsigned char	ocp;

	ocp = (*env).mem[((*data_p)[i].pc + 1) % MEM_SIZE];
	if (ft_test(env, (*data_p)[i].pc, ocp, 10) == 0)
	{
		r1 = (*env).mem[((*data_p)[i].pc + 2) % MEM_SIZE] - 1;
		octet_count = 3;
		ind2 = ((ocp & PARAM_2) >> 4 == DIR_CODE) ? \
			retrieve_dir_index(&(*data_p)[i], env, &octet_count, PARAM_2) : \
			retrieve_param(&(*data_p)[i], env, &octet_count, PARAM_2);
		ind3 = ((ocp & PARAM_3) >> 2 == DIR_CODE) ? \
			retrieve_dir_index(&(*data_p)[i], env, &octet_count, PARAM_3) : \
			retrieve_param(&(*data_p)[i], env, &octet_count, PARAM_3);
		if ((*env).verbose)
			ft_printf("Le processus %d fait un STI (r%hhu -> %d + %d).\n", \
				(*data_p)[i].nb, r1 + 1, ind2, ind3);
		ind3 = (*data_p)[i].pc + (ind2 + ind3) % IDX_MOD;
		ft_write_to_mem(env, ind3, (*data_p)[i].reg[r1]);
	}
	(*data_p)[i].pc = ((*data_p)[i].pc + 2 + ocp_value(ocp, 3, 2)) % MEM_SIZE;
	return (0);
}

int		do_lld(t_data_prog **data_prog, int i, t_env *env)
{
	int				param1;
	unsigned char	reg2;
	unsigned char	oct_cnt;
	unsigned char	ocp;

	ocp = (*env).mem[((*data_prog)[i].pc + 1) % MEM_SIZE];
	oct_cnt = 2;
	if (ft_test(env, (*data_prog)[i].pc, ocp, 12) == 0)
	{
		param1 = retrieve_param_nomod(&(*data_prog)[i], env, &oct_cnt, PARAM_1);
		reg2 = (*env).mem[((*data_prog)[i].pc + oct_cnt) % MEM_SIZE] - 1;
		(*data_prog)[i].reg[reg2] = param1;
		(*data_prog)[i].carry = ((*data_prog)[i].reg[reg2] == 0) ? 1 : 0;
		if ((*env).verbose)
			ft_printf("Le processus %d fait un LONG LOAD (%d -> r%hhu).\n", \
			(*data_prog)[i].nb, param1, reg2 + 1);
	}
	(*data_prog)[i].pc = ((*data_prog)[i].pc + 2 + ocp_value(ocp, 2, 4)) % \
		MEM_SIZE;
	return (0);
}

int		do_lldi(t_data_prog **data_p, int i, t_env *env)
{
	int				i1;
	int				i2;
	unsigned char	r3;
	unsigned char	oct_cnt;
	unsigned char	ocp;

	ocp = (*env).mem[((*data_p)[i].pc + 1) % MEM_SIZE];
	oct_cnt = 2;
	if (ft_test(env, (*data_p)[i].pc, ocp, 13) == 0)
	{
		i1 = ((ocp & PARAM_1) >> 6 == DIR_CODE) ? \
			retrieve_dir_index(&(*data_p)[i], env, &oct_cnt, PARAM_1) : \
			retrieve_param_nomod(&(*data_p)[i], env, &oct_cnt, PARAM_1);
		i2 = ((ocp & PARAM_2) >> 4 == DIR_CODE) ? \
			retrieve_dir_index(&(*data_p)[i], env, &oct_cnt, PARAM_2) : \
			retrieve_param_nomod(&(*data_p)[i], env, &oct_cnt, PARAM_2);
		r3 = (*env).mem[((*data_p)[i].pc + oct_cnt) % MEM_SIZE] - 1;
		(*data_p)[i].reg[r3] = retrieve_ind_val(&(*data_p)[i], env, i1 + i2);
		(*data_p)[i].carry = ((*data_p)[i].reg[r3] == 0) ? 1 : 0;
		if ((*env).verbose)
			ft_printf("Le proc. %d fait un LLDI (%d + %d-> r%hhu).\n", \
				(*data_p)[i].nb, i1, i2, r3 + 1);
	}
	(*data_p)[i].pc = ((*data_p)[i].pc + 2 + ocp_value(ocp, 3, 2)) % MEM_SIZE;
	return (0);
}
