/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framel <framel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 08:37:59 by framel            #+#    #+#             */
/*   Updated: 2017/03/17 14:39:16 by framel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

uint32_t	rev_endian(uint32_t octets)
{
	uint32_t ret;

	ret = 0;
	ret >>= 24;
	ret += octets & 0xFF;
	ret <<= 8;
	ret += octets >> 8 & 0xFF;
	ret <<= 8;
	ret += octets >> 16 & 0xFF;
	ret <<= 8;
	ret += octets >> 24 & 0xFF;
	return (ret);
}

TYPE		ft_divsup(TYPE n, TYPE d)
{
	TYPE q;
	TYPE r;

	if (d == 0)
		return (ft_error(NULL, DIVERR));
	r = n % d;
	q = n / d;
	if (r)
		return (q + 1);
	return (q);
}

uint8_t		isstreq(char *s1, char *s2)
{
	if (s1 == NULL || s2 == NULL)
		return (ft_error(NULL, STRERR));
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (FALSE);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (TRUE);
	return (FALSE);
}

uint8_t		ft_isext(char *file, char *ext)
{
	int	len;

	if (file == NULL || ext == NULL)
		return (ft_error(NULL, STRERR));
	len = 0;
	while (file[len])
		len++;
	while (len && file[len] != '.')
		len--;
	return (isstreq(&file[len], ext));
}

TYPE		ft_atoint(char *str, TYPE *nb)
{
	TYPE	i;

	i = 0;
	*nb = 0;
	if (ft_isint(str) == FALSE)
		return (ft_error(str, INTERR));
	while (str[i])
	{
		*nb += str[i] - '0';
		i++;
		if (str[i])
			*nb *= 10;
	}
	return (TRUE);
}
