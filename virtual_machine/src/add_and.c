/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_and.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestrue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 17:52:27 by rdestrue          #+#    #+#             */
/*   Updated: 2017/03/27 12:21:20 by rdestrue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		do_add(t_data_prog **data_p, int i, t_env *env)
{
	int				r1;
	int				r2;
	unsigned char	r3;
	unsigned char	ocp;

	ocp = (*env).mem[((*data_p)[i].pc + 1) % MEM_SIZE];
	if (ft_test(env, (*data_p)[i].pc, ocp, 3) == 0)
	{
		r1 = (*data_p)[i].reg[(*env).mem[((*data_p)[i].pc + 2) % MEM_SIZE] - 1];
		r2 = (*data_p)[i].reg[(*env).mem[((*data_p)[i].pc + 3) % MEM_SIZE] - 1];
		r3 = (*env).mem[((*data_p)[i].pc + 4) % MEM_SIZE] - 1;
		(*data_p)[i].reg[r3] = r1 + r2;
		(*data_p)[i].carry = ((*data_p)[i].reg[r3] == 0) ? 1 : 0;
		if ((*env).verbose)
			ft_printf("Le processus %d fait un ADD (r%hhu + r%hhu -> r%hhu).\n"\
			, (*data_p)[i].nb, (*env).mem[((*data_p)[i].pc + 2) % MEM_SIZE], \
			(*env).mem[((*data_p)[i].pc + 3) % MEM_SIZE], r3 + 1);
	}
	(*data_p)[i].pc = ((*data_p)[i].pc + 2 + ocp_value(ocp, 3, 4)) % MEM_SIZE;
	return (0);
}

int		do_sub(t_data_prog **data_p, int i, t_env *env)
{
	int				r1;
	int				r2;
	unsigned char	r3;
	unsigned char	ocp;

	ocp = (*env).mem[((*data_p)[i].pc + 1) % MEM_SIZE];
	if (ft_test(env, (*data_p)[i].pc, ocp, 4) == 0)
	{
		r1 = (*data_p)[i].reg[(*env).mem[((*data_p)[i].pc + 2) % MEM_SIZE] - 1];
		r2 = (*data_p)[i].reg[(*env).mem[((*data_p)[i].pc + 3) % MEM_SIZE] - 1];
		r3 = (*env).mem[((*data_p)[i].pc + 4) % MEM_SIZE] - 1;
		(*data_p)[i].reg[r3] = r1 - r2;
		(*data_p)[i].carry = ((*data_p)[i].reg[r3] == 0) ? 1 : 0;
		if ((*env).verbose)
			ft_printf("Le processus %d fait un SUB (r%hhu + r%hhu -> r%hhu).\n"\
			, (*data_p)[i].nb, (*env).mem[((*data_p)[i].pc + 2) % MEM_SIZE], \
			(*env).mem[((*data_p)[i].pc + 3) % MEM_SIZE], r3 + 1);
	}
	(*data_p)[i].pc = ((*data_p)[i].pc + 2 + ocp_value(ocp, 3, 4)) % MEM_SIZE;
	return (0);
}

int		do_and(t_data_prog **data_p, int i, t_env *env)
{
	int				param1;
	int				param2;
	unsigned char	reg3;
	unsigned char	octet_count;
	unsigned char	ocp;

	ocp = (*env).mem[(((*data_p)[i]).pc + 1) % MEM_SIZE];
	octet_count = 2;
	if (ft_test(env, (*data_p)[i].pc, ocp, 5) == 0)
	{
		param1 = retrieve_param(&(*data_p)[i], env, &octet_count, PARAM_1);
		param2 = retrieve_param(&(*data_p)[i], env, &octet_count, PARAM_2);
		reg3 = (*env).mem[((*data_p)[i].pc + octet_count) % MEM_SIZE] - 1;
		(*data_p)[i].reg[reg3] = param1 & param2;
		(*data_p)[i].carry = ((*data_p)[i].reg[reg3] == 0) ? 1 : 0;
		if ((*env).verbose)
			ft_printf("Le processus %d fait un AND (%d & %d -> r%hhu).\n", \
			(*data_p)[i].nb, param1, param2, reg3 + 1);
	}
	(*data_p)[i].pc = ((*data_p)[i].pc + 2 + ocp_value(ocp, 3, 4)) % MEM_SIZE;
	return (0);
}

int		do_or(t_data_prog **data_p, int i, t_env *env)
{
	int				param1;
	int				param2;
	unsigned char	reg3;
	unsigned char	octet_count;
	unsigned char	ocp;

	ocp = (*env).mem[((*data_p)[i].pc + 1) % MEM_SIZE];
	octet_count = 2;
	if (ft_test(env, (*data_p)[i].pc, ocp, 6) == 0)
	{
		param1 = retrieve_param(&(*data_p)[i], env, &octet_count, PARAM_1);
		param2 = retrieve_param(&(*data_p)[i], env, &octet_count, PARAM_2);
		reg3 = (*env).mem[((*data_p)[i].pc + octet_count) % MEM_SIZE] - 1;
		(*data_p)[i].reg[reg3] = param1 | param2;
		(*data_p)[i].carry = ((*data_p)[i].reg[reg3] == 0) ? 1 : 0;
		if ((*env).verbose)
			ft_printf("Le processus %d fait un OR (%d | %d -> r%hhu).\n", \
			(*data_p)[i].nb, param1, param2, reg3 + 1);
	}
	(*data_p)[i].pc = ((*data_p)[i].pc + 2 + ocp_value(ocp, 3, 4)) % MEM_SIZE;
	return (0);
}

int		do_xor(t_data_prog **data_p, int i, t_env *env)
{
	int				param1;
	int				param2;
	unsigned char	reg3;
	unsigned char	octet_count;
	unsigned char	ocp;

	ocp = (*env).mem[((*data_p)[i].pc + 1) % MEM_SIZE];
	octet_count = 2;
	if (ft_test(env, (*data_p)[i].pc, ocp, 7) == 0)
	{
		param1 = retrieve_param(&(*data_p)[i], env, &octet_count, PARAM_1);
		param2 = retrieve_param(&(*data_p)[i], env, &octet_count, PARAM_2);
		reg3 = (*env).mem[((*data_p)[i].pc + octet_count) % MEM_SIZE] - 1;
		(*data_p)[i].reg[reg3] = param1 ^ param2;
		(*data_p)[i].carry = ((*data_p)[i].reg[reg3] == 0) ? 1 : 0;
		if ((*env).verbose)
			ft_printf("Le processus %d fait un XOR (%d ^ %d -> r%hhu).\n", \
			(*data_p)[i].nb, param1, param2, reg3 + 1);
	}
	(*data_p)[i].pc = ((*data_p)[i].pc + 2 + ocp_value(ocp, 3, 4)) % MEM_SIZE;
	return (0);
}
