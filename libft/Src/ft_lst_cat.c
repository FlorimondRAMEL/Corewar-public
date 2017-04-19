/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_cat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestrue <rdestrue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/23 21:43:48 by rdestrue          #+#    #+#             */
/*   Updated: 2016/11/01 13:08:53 by rdestrue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lst_cat(t_list *first_list, t_list *second_list)
{
	t_list	*tmp;

	if (first_list == NULL)
		return (second_list);
	tmp = first_list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = second_list;
	return (first_list);
}
