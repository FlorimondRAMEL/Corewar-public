/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestrue <rdestrue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 23:35:08 by rdestrue          #+#    #+#             */
/*   Updated: 2016/01/21 22:38:27 by rdestrue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_addn(t_list *lst, t_list *new, int n, int i)
{
	t_list	*elt;

	if (lst->next == NULL)
		ft_lstaddend(&lst, new);
	else if (i == n)
	{
		elt = lst->next;
		lst->next = new;
		new->next = elt;
	}
	else
	{
		i++;
		ft_addn(lst->next, new, n, i);
	}
}

void		ft_lstaddn_or_end(t_list **alst, t_list *new, int n)
{
	t_list	*elt;

	if (n == 1)
		ft_lstadd(alst, new);
	else if (*alst == NULL)
		*alst = new;
	else if (n == 2)
	{
		elt = (*alst)->next;
		(*alst)->next = new;
		new->next = elt;
	}
	else if (n > 1 && (*alst)->next == NULL)
		ft_lstaddend(alst, new);
	else if (n > 1 && *alst != NULL && new != NULL)
		ft_addn((*alst)->next, new, n, 3);
}
