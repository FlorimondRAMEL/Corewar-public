/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framel <framel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 08:17:38 by framel            #+#    #+#             */
/*   Updated: 2017/03/28 21:00:37 by rdestrue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		ft_sort_files(t_file *f, TYPE n)
{
	TYPE	i;
	t_file	swp;

	i = 0;
	while (i < n - 1)
	{
		if (*f[i].n > *f[i + 1].n)
		{
			swp = f[i];
			f[i] = f[i + 1];
			f[i + 1] = swp;
			i = 0;
		}
		i++;
	}
}

static uint8_t	ft_isinfiles(t_file *f, TYPE nb, TYPE n, TYPE i)
{
	while (i < n)
	{
		if (f[i].n && *f[i].n == nb)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

static uint8_t	fill_n(t_file *f, TYPE n)
{
	TYPE	i;
	TYPE	cur;

	i = 0;
	cur = 0;
	while (i < n)
	{
		if (f[i].n == NULL)
		{
			if ((f[i].n = (TYPE *)ft_memalloc(sizeof(TYPE))) == NULL)
				return (ft_error("fill_n", MALLOCERR));
			while (ft_isinfiles(f, cur, n, 0) == TRUE)
				cur++;
			*f[i].n = cur;
			cur++;
		}
		else if (ft_isinfiles(f, *f[i].n, n, i + 1))
			return (ft_error(NULL, IDDUP));
		i++;
	}
	return (TRUE);
}

uint8_t			ft_run(t_file *f, TYPE n, t_env *e)
{
	t_data_prog	*d;

	if (fill_n(f, n) == FALSE)
		return (FALSE);
	ft_sort_files(f, n);
	if ((d = (t_data_prog *)ft_memalloc(sizeof(t_data_prog) * n)) == NULL)
		return (ft_error("t_data_prog", MALLOCERR));
	initialise(e, d, f, n);
	e->max_process_nb = d[n - 1].nb;
	e->current_winner = n - 1;
	if (ft_launch_battle(&d, e) == -1)
		return (ft_error("Fork", MALLOCERR));
	return (TRUE);
}
