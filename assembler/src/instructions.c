/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudra <hboudra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 16:22:59 by hboudra           #+#    #+#             */
/*   Updated: 2017/03/28 17:03:32 by framel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "asm.h"

bool		check_instruction(char *instruction)
{
	int		i;
	char	tmp[6];

	i = 0;
	ft_memset(tmp, 0, 6);
	while (instruction[i] != ' ' && instruction[i] != '\t' &&
			instruction[i] != '\0')
	{
		if (i >= 6)
			return (false);
		tmp[i] = instruction[i];
		++i;
	}
	i = 0;
	while (g_op_tab[i].instruction_name)
	{
		if (ft_strcmp(g_op_tab[i].instruction_name, tmp) == 0)
			return (true);
		i++;
	}
	return (false);
}

static char	*get_instruction(char *line, bool label_exist)
{
	int			i;

	i = skip(line);
	if (label_exist == true)
	{
		while (line[i] && line[i] != LABEL_CHAR)
			i++;
		if (line[i] == LABEL_END)
			i++;
		i += skip(&line[i]);
		if (line[i] == '\0')
			return (NULL);
	}
	if (check_instruction(&line[i]) == false)
		error(BAD_INSTRUCTION);
	return (&line[i]);
}

static void	norme(t_glob *glob, int *i, bool label_exist, char **line)
{
	char	*tmp;

	if ((tmp = get_instruction(*line, label_exist)) && *tmp)
	{
		if (parse_info(glob, tmp) != TRUE)
		{
			ft_strdel(line);
			error(MALLOC);
		}
		(*i)++;
	}
}

void		instructions(int fd, t_glob *glob)
{
	char		*line;
	bool		label_exist;
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (get_next_line(fd, &line) > 0)
	{
		label_exist = false;
		if (is_comment(line) == true)
		{
			ft_strdel(&line);
			continue ;
		}
		else if (ft_strchr(line, '#') || ft_strchr(line, ';'))
			replace_line(&line);
		parse_label(glob, line, i, &label_exist);
		norme(glob, &i, label_exist, &line);
		free(line);
		j = 1;
	}
	if (!j)
		error(NO_INSTRUCTIONS);
}
