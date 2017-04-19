/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudra <hboudra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 16:46:14 by hboudra           #+#    #+#             */
/*   Updated: 2017/03/28 22:34:02 by rdestrue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "asm.h"

static int	comment_check(char *str)
{
	int		space;
	int		len;
	int		i;

	space = skip(str);
	len = ft_strlen(COMMENT_CMD_STRING);
	i = 0;
	if (ft_strncmp(str + space, COMMENT_CMD_STRING, len))
		error(COM);
	space += len;
	space += (skip(&str[space]) + 1);
	while (str[space + i] && str[space + i] != '"')
		i++;
	if (i > COMMENT_LENGTH)
		error(COM);
	return (space);
}

static void	get_com(int fd, char *line, char **comment)
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
		if ((tmp = ft_strjoincat(*comment, line)) == NULL)
			error(MALLOC);
		ft_strdel(comment);
		*comment = tmp;
		if (count_char(*comment, '\"') >= 2)
		{
			ft_strdel(&line);
			break ;
		}
	}
}

void		comment_retrieve(int fd, t_header *header)
{
	char	*line;
	char	*comment;
	int		space;

	line = NULL;
	comment = NULL;
	get_com(fd, line, &comment);
	if (!comment)
		error(COM);
	space = comment_check(comment);
	ft_memset(header->comment, 0, PROG_NAME_LENGTH);
	check_quote(comment);
	if (comment[space] == '\"')
		ft_strcpy(header->comment, "No comment");
	else
		ft_strccat(header->comment, &comment[space], '\"');
	free(comment);
}
