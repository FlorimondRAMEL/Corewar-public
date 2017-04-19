/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_cpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestrue <rdestrue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/26 12:12:32 by rdestrue          #+#    #+#             */
/*   Updated: 2016/11/03 01:16:39 by rdestrue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lst_cpy(t_list *list)
{
	t_list	*list_cpy;
	t_list	*tmp;

	list_cpy = NULL;
	while (list)
	{
		tmp = ft_lstnew(list->content, list->content_size);
		ft_lstaddend(&list_cpy, tmp);
		list = list->next;
	}
	return (list_cpy);
}
