/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudra <hboudra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 20:01:28 by hboudra           #+#    #+#             */
/*   Updated: 2017/03/28 19:35:53 by rdestrue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "asm.h"

int		main(int ac, char **av)
{
	int			tab[2];
	char		*str[2192];
	char		*file;
	t_header	header;
	t_glob		glob;

	if (ac < 2)
		ft_putendl_fd("./asm	<champion.s> [...]", 2);
	ft_memset(tab, 0, sizeof(tab));
	while (++tab[0] < ac)
	{
		if (name(av[tab[0]]) == ERROR)
			error(NAME);
		ft_memset(str, 0, 2192);
		ft_memset(&header, 0, sizeof(header));
		glob.list = NULL;
		glob.label = NULL;
		parser(&glob, &header, av[tab[0]]);
		tab[1] = create(av[tab[0]], &file);
		write(tab[1], str, 2192);
		write_file(tab[1], header, glob);
		ft_printf("File %s is created\n", file);
		free(file);
	}
	return (0);
}
