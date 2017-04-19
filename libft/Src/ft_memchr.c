/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestrue <rdestrue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 23:42:00 by rdestrue          #+#    #+#             */
/*   Updated: 2016/01/03 23:27:01 by rdestrue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;
	void	*str;

	i = 0;
	str = (void *)s;
	while (i < n)
	{
		if (((unsigned char *)str)[i] == (unsigned char)c)
		{
			str = str + i;
			return (str);
		}
		i++;
	}
	str = NULL;
	return (str);
}
