/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestrue <rdestrue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/07 12:13:51 by rdestrue          #+#    #+#             */
/*   Updated: 2016/07/04 13:04:33 by rdestrue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t dstlen;
	size_t srclen;
	size_t i;
	size_t j;

	i = 0;
	srclen = ft_strlen(src);
	while (dst[i] != '\0' && i < size)
		i++;
	if (i == size || size == 0)
		return (size + srclen);
	else
	{
		dstlen = i;
		j = 0;
		while (src[j] != '\0' && i < size - 1)
		{
			dst[i] = src[j];
			i++;
			j++;
		}
	}
	dst[i] = '\0';
	return (dstlen + srclen);
}
