/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framel <framel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 04:16:50 by framel            #+#    #+#             */
/*   Updated: 2017/03/28 23:43:31 by rdestrue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static uint8_t	ft_read(int *fd, t_file *f, TYPE n)
{
	TYPE	i;

	i = 0;
	while (i < n)
	{
		if (read(fd[i], &f[i].h, sizeof(t_header)) != sizeof(t_header))
			return (ft_error(NULL, READERR));
		f[i].h.magic = rev_endian(f[i].h.magic);
		f[i].h.prog_size = rev_endian(f[i].h.prog_size);
		if (f[i].h.prog_size > CHAMP_MAX_SIZE)
			return (ft_error(f[i].h.prog_name, TOOBIG));
		if (f[i].h.magic != COREWAR_EXEC_MAGIC)
			return (ft_error(f[i].h.prog_name, FILERR));
		if ((f[i].p = (uint8_t *)ft_memalloc(f[i].h.prog_size)) == NULL)
			return (ft_error("prog", MALLOCERR));
		if (read(fd[i], f[i].p, f[i].h.prog_size) != f[i].h.prog_size)
			return (ft_error(NULL, READERR));
		i++;
	}
	return (TRUE);
}

static TYPE		ft_nopenfd(TYPE *lex, TYPE n_lex, int **fd, char **argv)
{
	TYPE	j;
	TYPE	k;
	TYPE	n;

	j = 0;
	k = 0;
	n = 0;
	*fd = (int *)ft_memalloc(sizeof(int) * n_lex);
	if (*fd == NULL)
		return (ft_error("fd", MALLOCERR));
	while (n < n_lex)
	{
		if (lex[j] & (1 << k))
		{
			if (((*fd)[n] = open(argv[j * TYPESIZE + k + 1], O_RDONLY)) < 3)
				return (ft_error(argv[j * TYPESIZE + k + 1], OPENERR));
			n++;
		}
		if (++k == TYPESIZE && ((k = 0) == 0))
			j++;
	}
	return (n);
}

static TYPE		ft_lex(TYPE **lex, TYPE argc, char **argv)
{
	TYPE	i;
	TYPE	j;
	TYPE	k;
	TYPE	n;

	i = 0;
	j = 0;
	k = 0;
	n = 0;
	*lex = (TYPE *)ft_memalloc(sizeof(TYPE) * ft_divsup(argc - 1, TYPESIZE));
	if (*lex == NULL)
		return (ft_error("lex", MALLOCERR));
	while (i < argc - 1)
	{
		if (ft_isext(argv[i + 1], ".cor"))
		{
			(*lex)[j] |= (1 << k);
			n++;
		}
		k++;
		if (k == TYPESIZE && ((k = 0) == 0))
			j++;
		i++;
	}
	return (ft_isext(argv[argc - 1], ".cor") ? n : INT_MAX);
}

static void		ft_free_files(t_file **files, TYPE n)
{
	while (n--)
	{
		free((*files)[n].p);
		free((*files)[n].n);
	}
	free(*files);
}

int				main(int argc, char **argv)
{
	TYPE	*lex;
	TYPE	n;
	int		*fd;
	t_file	*files;
	t_env	e;

	lex = 0;
	if (argc < 2)
		return (ft_error(NULL, NOFILE));
	if ((n = ft_lex(&lex, argc, argv)) < 1 || n > MAX_PLAYERS)
		return (ft_error_file(n));
	if (ft_nopenfd(lex, n, &fd, argv) != n)
		return (FALSE);
	free(lex);
	if ((files = (t_file *)ft_memalloc(sizeof(t_file) * n)) == NULL)
		return (ft_error("t_file", MALLOCERR));
	init_env(&e, n);
	if (ft_read(fd, files, n) == FALSE || \
		ft_getarg(files, argv, n, &e) == FALSE)
		return (FALSE);
	free(fd);
	if (ft_run(files, n, &e) == FALSE)
		return (FALSE);
	ft_free_files(&files, n);
	return (SUCCESS);
}
