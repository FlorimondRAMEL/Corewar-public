/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_aff.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestrue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 17:52:27 by rdestrue          #+#    #+#             */
/*   Updated: 2017/03/28 18:55:50 by rdestrue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		do_fork(t_data_prog **d_p, int i, t_env *env)
{
	int		j;
	short	ind;

	ind = (*env).mem[((*d_p)[i].pc + 1) % MEM_SIZE];
	ind = (ind << 8) + (*env).mem[((*d_p)[i].pc + 2) % MEM_SIZE];
	(*env).nb_usr += 1;
	*d_p = realloc(*d_p, sizeof(**d_p) * (*env).nb_usr);
	if (*d_p == NULL)
		return (-1);
	(*d_p)[(*env).nb_usr - 1].parent = (*d_p)[i].parent;
	(*d_p)[(*env).nb_usr - 1].nb = ++((*env).max_process_nb);
	j = -1;
	while (++j < REG_NUMBER)
		(*d_p)[(*env).nb_usr - 1].reg[j] = (*d_p)[i].reg[j];
	if ((*env).verbose)
		ft_printf("Le proc. %d fait un FORK à %hd.\n", (*d_p)[i].nb, \
			ind % IDX_MOD);
	ind = (*d_p)[i].pc + ind % IDX_MOD;
	(*d_p)[(*env).nb_usr - 1].pc = (ind < 0) ? MEM_SIZE + ind % MEM_SIZE : ind;
	(*d_p)[(*env).nb_usr - 1].carry = (*d_p)[i].carry;
	(*d_p)[(*env).nb_usr - 1].next_run_cycle = (*d_p)[i].next_run_cycle;
	(*d_p)[(*env).nb_usr - 1].last_live = (*d_p)[i].last_live;
	(*d_p)[(*env).nb_usr - 1].name = (*d_p)[i].name;
	(*d_p)[i].pc = ((*d_p)[i].pc + 3) % MEM_SIZE;
	return (0);
}

int		do_lfork(t_data_prog **d_p, int i, t_env *env)
{
	int		j;
	short	ind;

	ind = (*env).mem[((*d_p)[i].pc + 1) % MEM_SIZE];
	ind = (ind << 8) + (*env).mem[((*d_p)[i].pc + 2) % MEM_SIZE];
	(*env).nb_usr += 1;
	*d_p = realloc(*d_p, sizeof(**d_p) * (*env).nb_usr);
	if (*d_p == NULL)
		return (-1);
	(*d_p)[(*env).nb_usr - 1].parent = (*d_p)[i].parent;
	(*d_p)[(*env).nb_usr - 1].nb = ++((*env).max_process_nb);
	j = -1;
	while (++j < REG_NUMBER)
		(*d_p)[(*env).nb_usr - 1].reg[j] = (*d_p)[i].reg[j];
	if ((*env).verbose)
		ft_printf("Le proc. %d fait un LONG FORK à %hd.\n", (*d_p)[i].nb, ind);
	ind = (*d_p)[i].pc + ind;
	(*d_p)[(*env).nb_usr - 1].pc = (ind < 0) ? MEM_SIZE + ind % MEM_SIZE : ind;
	(*d_p)[(*env).nb_usr - 1].carry = (*d_p)[i].carry;
	(*d_p)[(*env).nb_usr - 1].next_run_cycle = (*d_p)[i].next_run_cycle;
	(*d_p)[(*env).nb_usr - 1].last_live = (*d_p)[i].last_live;
	(*d_p)[(*env).nb_usr - 1].name = (*d_p)[i].name;
	(*d_p)[i].pc = ((*d_p)[i].pc + 3) % MEM_SIZE;
	return (0);
}

int		do_aff(t_data_prog **data_p, int i, t_env *env)
{
	int				r1;
	unsigned char	ocp;

	ocp = (*env).mem[((*data_p)[i].pc + 1) % MEM_SIZE];
	if (((ocp & PARAM_1) >> 6) == REG_CODE && \
		(*env).mem[((*data_p)[i].pc + 2) % MEM_SIZE] > 0 && \
		(*env).mem[((*data_p)[i].pc + 2) % MEM_SIZE] <= REG_NUMBER)
	{
		r1 = (*data_p)[i].reg[(*env).mem[((*data_p)[i].pc + 2) % MEM_SIZE] - 1];
		if ((*env).verbose)
			ft_printf("Le processus %d fait un AFF (%d).\n", (*data_p)[i].nb, \
				r1 % 256);
		ft_putchar(r1 % 256);
		ft_putchar('\n');
	}
	(*data_p)[i].pc = ((*data_p)[i].pc + 2 + ocp_value(ocp, 1, 4)) % MEM_SIZE;
	return (0);
}
