/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestrue <rdestrue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/11 23:26:23 by rdestrue          #+#    #+#             */
/*   Updated: 2016/01/21 22:41:29 by rdestrue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_test_strstr(const char *big, const char *little, int i)
{
	int j;

	i = i + 1;
	j = 1;
	while (little[j] != '\0')
	{
		if (big[i] != little[j])
			return (0);
		i++;
		j++;
	}
	return (1);
}

char		*ft_strstr(const char *big, const char *little)
{
	int		i;
	int		x;
	char	*ptr;

	if (little[0] == '\0')
		return ((char *)big);
	ptr = NULL;
	i = 0;
	x = 0;
	while (big[i] != '\0')
	{
		if (big[i] == little[0])
		{
			x = ft_test_strstr(big, little, i);
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
