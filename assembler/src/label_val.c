/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label_val.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudra <hboudra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 19:59:25 by hboudra           #+#    #+#             */
/*   Updated: 2017/03/28 17:02:46 by framel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	help(int line, int label, t_glob glob)
{
	int		i;
	t_info	*info;
	int		ret;

	if (line == label)
		return (0);
	i = 0;
	info = glob.list;
	ret = 0;
	while (info)
	{
		if (line < label && i >= line && i < label)
			ret += count_byte_inst(info);
		else if (line > label && i >= label && i < line)
			ret += count_byte_inst(info);
		i++;
		info = info->next;
	}
	if (line > label)
		return (-1 * ret);
	else
		return (ret);
}

static int	get_cur_inst(t_info *info, t_glob glob)
{
	int		cur;
	t_info	*tmp;

	cur = 0;
	tmp = glob.list;
	while (tmp && tmp != info)
	{
		cur++;
		tmp = tmp->next;
	}
	return (cur);
}

int			get_label_val(t_info *info, t_glob glob, int i)
{
	int		label;
	int		line;
	t_list	*lst_lab;
	char	*str;

	lst_lab = glob.label;
	line = get_cur_inst(info, glob);
	str = info->param[i];
	while (str && *str && *str != ':')
		str++;
	str++;
	while (lst_lab && ft_strcmp(str, L_STR(lst_lab)))
		lst_lab = lst_lab->next;
	if (!lst_lab)
		error(BAD_LABEL_FORMAT);
	label = ((t_label*)(lst_lab->content))->n_inst;
	return (help(line, label, glob));
}
