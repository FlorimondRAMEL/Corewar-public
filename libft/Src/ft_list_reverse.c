/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_reverse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestrue <rdestrue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 23:35:53 by rdestrue          #+#    #+#             */
/*   Updated: 2016/10/18 23:37:12 by rdestrue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_list_reverse(t_list **alst)
{
	t_list *tmp;
	t_list *prev;

	if (*alst != NULL)
	{
		tmp = NULL;
		prev = NULL;
		while ((*alst)->next != NULL)
		{
			tmp = (*alst)->next;
			(*alst)->next = prev;
			prev = *alst;
			*alst = tmp;
		}
		(*alst)->next = prev;
	}
}
