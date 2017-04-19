/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestrue <rdestrue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 23:35:08 by rdestrue          #+#    #+#             */
/*   Updated: 2016/11/01 13:10:47 by rdestrue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstaddend(t_list **alst, t_list *new)
{
	if (*alst != NULL)
	{
		if ((*alst)->next != NULL)
			ft_lstaddend(&(*alst)->next, new);
		else
			(*alst)->next = new;
	}
	else if (*alst == NULL)
		*alst = new;
}
