/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framel <framel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 22:58:09 by framel            #+#    #+#             */
/*   Updated: 2017/03/27 20:39:10 by framel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

TYPE			*ft_parseint(char ***argv)
{
	TYPE	i;
	TYPE	n;
	char	**ptr;
	TYPE	*arr;

	i = 1;
	n = 0;
	(*argv)++;
	ptr = *argv;
	while (ft_isint(*(ptr++)))
		n++;
	if (n == FALSE)
		return (FALSE);
	arr = (TYPE *)ft_memalloc(sizeof(TYPE) * (n + 1));
	if (arr == NULL)
		return (NULL);
	arr[0] = n;
	while (i < n + 1)
	{
		if (ft_atoint(**argv, &arr[i++]) == FALSE)
			return (NULL);
		(*argv)++;
	}
	return (arr);
}

static uint8_t	ft_getsecondarg(t_env *e, char ***argv, t_file *f, TYPE i)
{
	if (isstreq(**argv, "-d") || isstreq(**argv, "-dump"))
	{
		(*argv)++;
		if (ft_atoint(*((*argv)++), &e->dump) == FALSE)
			return (ft_error(NULL, DUMPERR));
		return (TRUE);
	}
	else if (isstreq(**argv, "-n"))
	{
		(*argv)++;
		if ((f[i].n = (TYPE *)ft_memalloc(sizeof(TYPE))) == NULL)
			return (ft_error("ft_getarg", MALLOCERR));
		if (ft_atoint(*((*argv)++), f[i].n) == FALSE)
			return (ft_error(NULL, IDERR));
		if (*f[i].n > INT_MAX)
			return (ft_error("-n", TOOLARGE));
		return (TRUE);
	}
	else
		return (2);
}

static uint8_t	ft_getfirstarg(t_env *e, char ***argv, t_file *f, TYPE i)
{
	if (isstreq(**argv, "-z"))
	{
		(*argv)++;
		e->zaz_opt = -1;
		return (TRUE);
	}
	else if (isstreq(**argv, "-v"))
	{
		(*argv)++;
		e->verbose = 1;
		e->silent = 0;
		return (TRUE);
	}
	else if (isstreq(**argv, "-s"))
	{
		(*argv)++;
		if (e->verbose == 0)
			e->silent = 1;
		return (TRUE);
	}
	else
		return (ft_getsecondarg(e, argv, f, i));
}

uint8_t			ft_getarg(t_file *f, char **argv, TYPE n, t_env *e)
{
	TYPE	i;
	uint8_t ok;

	i = 0;
	argv++;
	while (i < n)
	{
		ok = ft_getfirstarg(e, &argv, f, i);
		if (ok == FALSE)
			return (FALSE);
		else if (ok == 2 && ft_isext(*argv, ".cor"))
		{
			argv++;
			i++;
		}
		else if (ok == 2)
			return (ft_error(*argv, ARGERR));
	}
	return (TRUE);
}
