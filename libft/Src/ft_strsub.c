/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestrue <rdestrue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/20 00:41:30 by rdestrue          #+#    #+#             */
/*   Updated: 2016/01/18 22:21:01 by rdestrue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char			*str;
	unsigned int	i;

	str = ft_strnew(len);
	if (str == NULL)
		return (str);
	i = 0;
	while (i < (unsigned int)len)
	{
		str[i] = s[i + start];
		i++;
	}
	return (str);
}
