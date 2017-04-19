/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestrue <rdestrue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/20 20:03:20 by rdestrue          #+#    #+#             */
/*   Updated: 2016/01/21 22:49:39 by rdestrue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_new_elt(t_list **alst, char *str, int j)
{
	t_list *elt;

	elt = ft_lstnew(str, j + 1);
	ft_lstaddend(alst, elt);
	ft_strclr(str);
}

static size_t	ft_split_list(t_list **alst, char const *s, char *str, char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c && j == 0)
			i++;
		else if (s[i] == c)
		{
			ft_new_elt(alst, str, j);
			j = 0;
			i++;
		}
		else
		{
			str[j] = s[i];
			j++;
			i++;
		}
	}
	return (j);
}

t_list			*ft_strsplit_list(char const *s, char c)
{
	t_list	**alst;
	t_list	*lst;
	t_list	*elt;
	size_t	len;
	char	*str;

	len = ft_strlen(s);
	if (len == 0)
		return (NULL);
	str = ft_strnew(len);
	lst = NULL;
	alst = &lst;
	len = ft_split_list(alst, s, str, c);
	if (str[0] != '\0')
	{
		elt = ft_lstnew(str, len + 1);
		ft_lstaddend(alst, elt);
	}
	return (*alst);
}
