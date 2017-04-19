/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_instr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestrue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 17:52:27 by rdestrue          #+#    #+#             */
/*   Updated: 2017/03/28 08:25:08 by rdestrue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int	ft_run_proc(t_data_prog **data_prog, int i, t_env *env)
{
	if ((*data_prog)[i].next_instr > 0 && \
		(*data_prog)[i].next_instr <= INSTRUCTIONS_NB)
	{
		if (g_fct_ptr[(*data_prog)[i].next_instr - 1](data_prog, i, env) == -1)
		{
			free(*data_prog);
			return (-1);
		}
	}
	else
		(*data_prog)[i].pc += 1;
	return (0);
}

int			ft_run_cycle(t_data_prog **data_prog, t_env *env)
{
	int			i;

	if ((*env).verbose)
		ft_printf("Cycle %d\n", (*env).cycle);
	i = (*env).nb_usr - 1;
	while (i >= 0)
	{
		if ((*data_prog)[i].last_live >= 0 && \
				(*data_prog)[i].next_run_cycle < (*env).cycle)
			ft_init_run_cycle(&(*data_prog)[i], env);
		if ((*data_prog)[i].last_live >= 0 && \
				(*data_prog)[i].next_run_cycle == (*env).cycle)
		{
			if (ft_run_proc(data_prog, i, env) == -1)
				return (-1);
		}
		i--;
	}
	return (0);
}

void		ft_init_run_cycle(t_data_prog *data_prog, t_env *env)
{
	if ((*env).mem[(*data_prog).pc % MEM_SIZE] > 0 && \
		(*env).mem[(*data_prog).pc % MEM_SIZE] <= INSTRUCTIONS_NB)
	{
		(*data_prog).next_run_cycle += \
			g_op_tab[(*env).mem[(*data_prog).pc % MEM_SIZE] - 1].nb_cycles;
		(*data_prog).next_instr = (*env).mem[(*data_prog).pc % MEM_SIZE];
	}
	else
	{
		(*data_prog).next_run_cycle += 1;
		(*data_prog).next_instr = 0;
	}
}

void		init_instructions(void)
{
	g_fct_ptr[0] = &do_live;
	g_fct_ptr[1] = &do_ld;
	g_fct_ptr[2] = &do_st;
	g_fct_ptr[3] = &do_add;
	g_fct_ptr[4] = &do_sub;
	g_fct_ptr[5] = &do_and;
	g_fct_ptr[6] = &do_or;
	g_fct_ptr[7] = &do_xor;
	g_fct_ptr[8] = &do_zjmp;
	g_fct_ptr[9] = &do_ldi;
	g_fct_ptr[10] = &do_sti;
	g_fct_ptr[11] = &do_fork;
	g_fct_ptr[12] = &do_lld;
	g_fct_ptr[13] = &do_lldi;
	g_fct_ptr[14] = &do_lfork;
	g_fct_ptr[15] = &do_aff;
}
