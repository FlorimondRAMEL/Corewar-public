/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudra <hboudra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 18:49:22 by hboudra           #+#    #+#             */
/*   Updated: 2017/03/28 22:34:26 by rdestrue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "asm.h"

static int	name_check(char *str)
{
	int		space;
	int		len;
	int		i;

	space = skip(str);
	len = ft_strlen(NAME_CMD_STRING);
	i = 0;
	if (ft_strncmp(str + space, NAME_CMD_STRING, len))
		error(NAME_2);
	space += len;
	space += (skip(&str[space]) + 1);
	while (str[space + i] && str[space + i] != '"')
		i++;
	if (i > PROG_NAME_LENGTH)
		error(NAME_3);
	return (space);
}

static void	get_name(int fd, char *line, char **name)
{
	char	*tmp;

	tmp = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		if (is_comment(line))
		{
			ft_strdel(&line);
			continue ;
		}
		if ((tmp = ft_strjoincat(*name, line)) == NULL)
			error(MALLOC);
		ft_strdel(name);
		*name = tmp;
		if (count_char(*name, '\"') >= 2)
		{
			ft_strdel(&line);
			break ;
		}
	}
}

void		name_retrieve(int fd, t_header *header)
{
	char	*line;
	char	*name;
	int		space;

	line = NULL;
	name = NULL;
	get_name(fd, line, &name);
	if (!name)
		error(NAME_2);
	space = name_check(name);
	ft_memset(header->prog_name, 0, PROG_NAME_LENGTH);
	check_quote(name);
	if (name[space] == '\"')
		ft_strcpy(header->prog_name, "John Doe");
	else
		ft_strccat(header->prog_name, &name[space], '\"');
	free(name);
}
