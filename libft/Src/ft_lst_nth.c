/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_nth.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestrue <rdestrue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/23 21:43:48 by rdestrue          #+#    #+#             */
/*   Updated: 2016/09/23 22:12:27 by rdestrue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lst_nth(t_list *list, int position)
{
	if (list == NULL || position > ft_list_size(list))
		return (NULL);
	position--;
	while (position)
	{
		list = list->next;
		position--;
	}
	return (list);
}
