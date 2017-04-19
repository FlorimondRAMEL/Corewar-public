/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_free_one.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestrue <rdestrue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/26 12:12:32 by rdestrue          #+#    #+#             */
/*   Updated: 2016/11/03 20:49:34 by rdestrue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lst_free_one(t_list **list, t_list *elt)
{
	t_list	*tmp;

	if (elt == *list)
	{
		*list = (*list)->next;
		free(elt->content);
		free(elt);
	}
	else
	{
		tmp = *list;
		while (tmp && tmp->next != elt)
			tmp = tmp->next;
		if (tmp->next == elt)
		{
			tmp->next = elt->next;
			free(elt->content);
			free(elt);
		}
	}
}
