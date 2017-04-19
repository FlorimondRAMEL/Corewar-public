/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfold.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestrue <rdestrue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 20:30:15 by rdestrue          #+#    #+#             */
/*   Updated: 2016/01/21 22:09:49 by rdestrue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_lstfold(t_list *lst, void *(*f)(void *ct1, void *ct2), void *init)
{
	void	*result;
	t_list	*tmp;

	if (lst == NULL)
		return (NULL);
	tmp = lst;
	result = f(init, tmp->content);
	tmp = tmp->next;
	while (tmp != NULL)
	{
		result = f(result, tmp->content);
		tmp = tmp->next;
	}
	return (result);
}
