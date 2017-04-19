/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudra <hboudra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 18:07:18 by hboudra           #+#    #+#             */
/*   Updated: 2017/03/28 17:00:34 by framel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "asm.h"

void	replace_line(char **line)
{
	char	*tmp;

	tmp = *line;
	if (ft_strchr(*line, ';') && !ft_strchr(*line, '#'))
	{
		*line = ft_strsub(*line, 0, ft_strchr(*line, ';') - *line);
		ft_strdel(&tmp);
	}
	else if (!ft_strchr(*line, ';') && ft_strchr(*line, '#'))
	{
		*line = ft_strsub(*line, 0, ft_strchr(*line, '#') - *line);
		ft_strdel(&tmp);
	}
	else if (ft_strchr(*line, ';') && ft_strchr(*line, '#'))
	{
		if (ft_strchr(*line, ';') > ft_strchr(*line, '#'))
			*line = ft_strsub(*line, 0, ft_strchr(*line, '#') - *line);
		else
			*line = ft_strsub(*line, 0, ft_strchr(*line, ';') - *line);
		ft_strdel(&tmp);
	}
}

int		count_char(char *str, char c)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (str[i])
	{
		if (str[i] == c)
			ret++;
		i++;
	}
	return (ret);
}

int		is_comment(char *str)
{
	int	i;

	i = skip(str);
	if (str[i] == COMMENT_CHAR || str[i] == '\0' || str[i] == ';')
		return (TRUE);
	return (FALSE);
}

int		skip(char *str)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]) == true)
		i++;
	return (i);
}
