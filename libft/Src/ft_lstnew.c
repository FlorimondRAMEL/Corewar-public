/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestrue <rdestrue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 12:31:52 by rdestrue          #+#    #+#             */
/*   Updated: 2016/10/30 13:35:52 by rdestrue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *elt;

	elt = (t_list *)malloc(sizeof(t_list));
	if (elt == NULL)
		return (NULL);
	if (content == NULL)
	{
		elt->content = NULL;
		elt->content_size = 0;
	}
	else
	{
		elt->content = malloc(content_size);
		if (elt->content == NULL)
			return (NULL);
		ft_memcpy(elt->content, content, content_size);
		elt->content_size = content_size;
	}
	elt->next = NULL;
	return (elt);
}
