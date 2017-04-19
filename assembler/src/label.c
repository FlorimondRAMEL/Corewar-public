/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudra <hboudra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 10:50:07 by hboudra           #+#    #+#             */
/*   Updated: 2017/03/28 17:01:14 by framel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "asm.h"

void	replace_label_char(t_glob *glob)
{
	t_list	*label;

	label = glob->label;
	while (label)
	{
		*ft_strchr(L_STR(label), ':') = '\0';
		label = label->next;
	}
}

bool	check_label_2(char *label)
{
	int	i;
	int	len_label;

	i = 0;
	len_label = ft_strlen(label);
	if (label[len_label - 1] != ':')
		return (false);
	while (i < len_label - 1)
	{
		if (ft_strchr(LABEL_CHARS, label[i]) == NULL)
			return (false);
		i++;
	}
	return (true);
}

char	*check_label(char *line)
{
	int		i;
	int		count_car_label;
	char	*label;

	i = skip(line);
	count_car_label = 0;
	label = NULL;
	while (line[i] != '\0' && ft_isspace(line[i]) == false)
	{
		++count_car_label;
		++i;
	}
	label = ft_strndup(&line[skip(line)], count_car_label);
	if (label[count_car_label - 1] == ':')
		return (label);
	free(label);
	return (0);
}

void	parse_label(t_glob *glob, char *line, int i, bool *label_exist)
{
	char	*label;
	t_label	info;
	t_list	*tmp;

	if ((label = check_label(line)))
	{
		*label_exist = true;
		if (check_label_2(label) == false)
			error(BAD_LABEL);
		info.str = label;
		info.n_inst = i;
		if (!(tmp = ft_lstnew(&info, sizeof(info))))
			error(MALLOC);
		ft_lstadd(&glob->label, tmp);
	}
}
