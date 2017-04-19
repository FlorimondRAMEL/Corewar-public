/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framel <framel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 22:52:10 by framel            #+#    #+#             */
/*   Updated: 2017/03/27 20:42:06 by framel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

TYPE	ft_nbrlen(TYPE nb)
{
	TYPE	i;

	i = 1;
	while (nb /= 10)
		i++;
	return (i);
}

char	*ft_inttoa(TYPE nb)
{
	TYPE len;
	char *str;

	len = ft_nbrlen(nb);
	str = (char *)ft_memalloc(sizeof(char) * len);
	if (str == NULL)
		return (NULL);
	str[len] = '\0';
	while (len--)
	{
		str[len] = (nb % 10) + 48;
		nb /= 10;
	}
	return (str);
}

uint8_t	ft_isint_next(char *str, char *strmax, TYPE len)
{
	uint8_t i;

	i = 0;
	if (len == ft_strlen(strmax))
	{
		while (str[i])
		{
			if (str[i] > strmax[i])
			{
				free(strmax);
				return (FALSE);
			}
			if (str[i] < strmax[i])
			{
				free(strmax);
				return (TRUE);
			}
			i++;
		}
	}
	free(strmax);
	return (TRUE);
}

uint8_t	ft_isint(char *str)
{
	uint8_t i;
	TYPE	len;
	char	*strmax;

	i = 0;
	len = ft_strlen(str);
	strmax = ft_inttoa(TYPE_MAX);
	if (strmax == NULL)
		return (FALSE);
	if (len > ft_strlen(strmax))
	{
		free(strmax);
		return (FALSE);
	}
	while (str[i])
	{
		if (ft_isdigit(str[i++]) == FALSE)
		{
			free(strmax);
			return (FALSE);
		}
	}
	return (ft_isint_next(str, strmax, len));
}
