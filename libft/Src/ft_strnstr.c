/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestrue <rdestrue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/11 23:26:23 by rdestrue          #+#    #+#             */
/*   Updated: 2016/01/21 22:56:47 by rdestrue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		ft_test(const char *big, const char *lit, size_t i, size_t len)
{
	int j;

	i = i + 1;
	j = 1;
	while (lit[j] != '\0' && i < len)
	{
		if (big[i] != lit[j])
			return (0);
		i++;
		j++;
	}
	if (i == len && lit[j] != '\0')
		return (0);
	return (1);
}

char			*ft_strnstr(const char *big, const char *lit, size_t len)
{
	size_t	i;
	int		x;
	char	*ptr;

	if (lit[0] == '\0')
		return ((char *)big);
	ptr = NULL;
	i = 0;
	x = 0;
	while (big[i] != '\0' && i < len)
	{
		if (big[i] == lit[0])
		{
			x = ft_test(big, lit, i, len);
			if (x == 1)
			{
				ptr = (char *)&big[i];
				return (ptr);
			}
		}
		i++;
	}
	return (ptr);
}
