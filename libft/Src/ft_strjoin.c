/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestrue <rdestrue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/20 00:41:30 by rdestrue          #+#    #+#             */
/*   Updated: 2016/01/18 22:21:26 by rdestrue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*str;
	size_t			i;
	size_t			len;
	size_t			lens1;

	len = ft_strlen(s1) + ft_strlen(s2);
	str = ft_strnew(len);
	if (str == NULL)
		return (str);
	i = 0;
	lens1 = ft_strlen(s1);
	while (i < lens1)
	{
		str[i] = s1[i];
		i++;
	}
	while (i < len)
	{
		str[i] = s2[i - lens1];
		i++;
	}
	return (str);
}
