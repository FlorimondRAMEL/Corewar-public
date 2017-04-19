/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestrue <rdestrue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/15 23:20:51 by rdestrue          #+#    #+#             */
/*   Updated: 2016/06/17 12:51:53 by rdestrue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*str;
	size_t	i;

	i = 0;
	str = (char *)malloc(sizeof(*str) * (size + 1));
	if (str == NULL)
		return (str);
	else
	{
		while (i < (size + 1))
		{
			str[i] = '\0';
			i++;
		}
	}
	return (str);
}
