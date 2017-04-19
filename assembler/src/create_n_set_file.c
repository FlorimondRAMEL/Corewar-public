/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_n_set_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudra <hboudra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 13:43:18 by hboudra           #+#    #+#             */
/*   Updated: 2017/03/28 19:34:03 by rdestrue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <fcntl.h>

static void	write_magic(int fd)
{
	lseek(fd, 0, SEEK_SET);
	ft_fprintf(fd, "%c", 0);
	lseek(fd, 1, SEEK_SET);
	ft_fprintf(fd, "%c", 234);
	lseek(fd, 2, SEEK_SET);
	ft_fprintf(fd, "%c", 131);
	lseek(fd, 3, SEEK_SET);
	ft_fprintf(fd, "%c", 243);
}

int			create(char *arg, char **file)
{
	int		fd;
	int		i;

	i = ft_strlen(arg);
	if (!(*file = ft_strnew(i + 2)))
		error(MALLOC);
	ft_strcat(*file, arg);
	i -= 1;
	(*file)[i] = 'c';
	ft_strcat(*file, "or");
	if ((fd = open(*file, O_RDWR | O_CREAT | O_TRUNC, S_IRWXU)) < 0)
		error(CREATING_FILE);
	return (fd);
}

void		write_file(int fd, t_header header, t_glob glob)
{
	write_magic(fd);
	lseek(fd, 4, SEEK_SET);
	ft_fprintf(fd, "%s", header.prog_name);
	lseek(fd, 132, SEEK_SET);
	write_nb_inst(glob.list, fd);
	lseek(fd, 140, SEEK_SET);
	ft_fprintf(fd, "%s", header.comment);
	lseek(fd, 0, SEEK_END);
	write_param(fd, glob);
	close(fd);
}
