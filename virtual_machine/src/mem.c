/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framel <framel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 00:49:25 by framel            #+#    #+#             */
/*   Updated: 2017/03/27 21:01:09 by framel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			init_env(t_env *e, TYPE n)
{
	ft_bzero(e, sizeof(t_env));
	e->dump = (uint32_t)-1;
	e->nb_usr = n;
	e->zaz_opt = 1;
	e->live_counter = 1;
	e->nb_cycles_to_die = CYCLE_TO_DIE;
	e->next_check = e->nb_cycles_to_die;
	init_instructions();
}

static void		ft_load(uint8_t *mem, uint8_t *p, uint32_t size, TYPE addr)
{
	mem += addr;
	while (size--)
	{
		*mem = *p;
		mem++;
		p++;
	}
}

void			initialise(t_env *e, t_data_prog *d, t_file *f, TYPE n)
{
	TYPE	i;

	i = 0;
	while (i < n)
	{
		d[i].nb = *f[i].n;
		d[i].parent = d[i].nb;
		d[i].pc = (MEM_SIZE / n) * i;
		d[i].last_live = 0;
		d[i].name = f[i].h.prog_name;
		d[i].reg[0] = e->zaz_opt * d[i].parent;
		ft_load(e->mem, f[i].p, f[i].h.prog_size, d[i].pc);
		ft_init_run_cycle(&d[i], e);
		i++;
	}
}
