/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   battle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestrue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 17:52:27 by rdestrue          #+#    #+#             */
/*   Updated: 2017/03/28 19:09:51 by rdestrue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	ft_kill(t_data_prog *data_prog, t_env *env)
{
	int			i;

	i = (*env).nb_usr - 1;
	while (i >= 0)
	{
		if (data_prog[i].last_live >= 0 && data_prog[i].last_live <= \
			(int)(*env).cycle - (*env).nb_cycles_to_die)
		{
			if (!(*env).silent)
			{
				ft_printf("Le processus %d n'a pas donné ", data_prog[i].nb);
				ft_printf("signe de vie depuis %d cycles (CTD = %d).\n", \
				(*env).cycle - data_prog[i].last_live, (*env).nb_cycles_to_die);
			}
			data_prog[i].last_live = -1;
		}
		i--;
	}
}

static char	ft_check_alive(t_data_prog *data_prog, t_env *env)
{
	int			i;
	char		ret;

	ret = 0;
	i = (*env).nb_usr - 1;
	while (ret == 0 && i >= 0)
	{
		if (data_prog[i].last_live >= 0)
			ret = 1;
		i--;
	}
	return (ret);
}

static void	ft_checks_cycles(t_data_prog **data_prog, t_env *env)
{
	ft_kill(*data_prog, env);
	((*env).nb_checks)++;
	if ((*env).live_counter >= NBR_LIVE || (*env).nb_checks == 10)
	{
		(*env).nb_cycles_to_die -= CYCLE_DELTA;
		(*env).nb_checks = 0;
	}
	(*env).next_check += (*env).nb_cycles_to_die;
	(*env).live_counter = 0;
}

int			ft_launch_battle(t_data_prog **data_prog, t_env *env)
{
	while (ft_check_alive(*data_prog, env) == 1)
	{
		if ((*env).cycle == (*env).dump)
		{
			print_memory((*env).mem, MEM_SIZE);
			exit(0);
		}
		(*env).cycle += 1;
		if (ft_run_cycle(data_prog, env) == -1)
			return (-1);
		if ((*env).cycle >= (*env).next_check)
			ft_checks_cycles(data_prog, env);
	}
	ft_printf("Le joueur %d (%s) est déclaré gagnant au cycle %d.\n", \
		(*data_prog)[(*env).current_winner].nb, \
		(*data_prog)[(*env).current_winner].name, (*env).cycle);
	free(*data_prog);
	return (0);
}
