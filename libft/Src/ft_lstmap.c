/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestrue <rdestrue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 23:40:14 by rdestrue          #+#    #+#             */
/*   Updated: 2016/01/21 22:50:47 by rdestrue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*ft_mrec(t_list *lst, t_list *(*f)(t_list *elem), t_list **alst)
{
	t_list *elt;

	if (lst->next != NULL)
	{
		elt = ft_mrec(lst->next, f, alst);
		if (elt == NULL)
			return (NULL);
	}
	elt = f(lst);
	if (elt == NULL)
		return (NULL);
	ft_lstaddend(alst, elt);
	return (elt);
}

t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*elt;
	t_list	*alst;

	elt = f(lst);
	if (elt == NULL)
		return (NULL);
	alst = elt;
	elt = ft_mrec(lst->next, f, &alst);
	if (elt == NULL)
		return (NULL);
	return (alst);
}
