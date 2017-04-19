/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestrue <rdestrue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/20 21:44:30 by rdestrue          #+#    #+#             */
/*   Updated: 2016/01/21 22:37:58 by rdestrue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_nblen(int n, size_t *len)
{
	if (n > 0)
		n = -n;
	if (n <= -10)
		ft_nblen(n / 10, len);
	(*len)++;
}

static void	ft_putnbrstr(char *str, int n, int *i)
{
	if (n > 0)
		n = -n;
	if (n <= -10)
		ft_putnbrstr(str, n / 10, i);
	str[*i] = (-(n % 10) + '0');
	(*i)++;
}

char		*ft_itoa(int n)
{
	size_t	len;
	char	*str;
	int		i;

	len = 0;
	if (n < 0)
		len = 1;
	ft_nblen(n, &len);
	str = ft_strnew(len);
	if (str == NULL)
		return (str);
	i = 0;
	if (n < 0)
	{
		str[i] = '-';
		i++;
	}
	ft_putnbrstr(str, n, &i);
	return (str);
}
