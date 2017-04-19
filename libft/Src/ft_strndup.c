/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framel <framel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 17:45:54 by framel            #+#    #+#             */
/*   Updated: 2017/03/27 17:46:07 by framel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t nb)
{
	char	*dst;
	size_t	len;

	len = ft_strlen(s1);
	if (nb < len)
		len = nb;
	dst = (char *)malloc(sizeof(char) * (nb + 1));
	if (dst == NULL)
		return (NULL);
	dst[nb] = '\0';
	return ((char *)ft_memcpy(dst, s1, nb));
}
