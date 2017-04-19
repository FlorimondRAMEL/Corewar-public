/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wcharconv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestrue <rdestrue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/01 12:45:32 by rdestrue          #+#    #+#             */
/*   Updated: 2016/08/16 18:58:33 by rdestrue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_wcharconv3and4(wchar_t wc, int i)
{
	char	*str;

	if (i == 3)
	{
		str = ft_strnew(3);
		if (str == NULL)
			return (NULL);
		str[0] = (wc >> 12) + 0xE0;
		str[1] = ((wc >> 6) & 0x3F) + 0x80;
		str[2] = (wc & 0x3F) + 0x80;
	}
	else
	{
		str = ft_strnew(4);
		if (str == NULL)
			return (NULL);
		str[0] = (wc >> 18) + 0xF0;
		str[1] = ((wc >> 12) & 0x3F) + 0x80;
		str[2] = ((wc >> 6) & 0x3F) + 0x80;
		str[3] = (wc & 0x3F) + 0x80;
	}
	return (str);
}

char		*ft_wcharconv(wchar_t wc)
{
	char	*str;

	str = NULL;
	if (wc < 0)
		return (str);
	if (wc <= 0x7F)
	{
		str = ft_strnew(1);
		if (str == NULL)
			return (NULL);
		str[0] = wc;
	}
	else if (wc <= 0x7FF)
	{
		str = ft_strnew(2);
		if (str == NULL)
			return (NULL);
		str[0] = (wc >> 6) + 0xC0;
		str[1] = (wc & 0x3F) + 0x80;
	}
	else if (wc < 0xD800 || (wc > 0xDFFF && wc <= 0xFFFF))
		str = ft_wcharconv3and4(wc, 3);
	else if (wc > 0xFFFF && wc <= 0x10FFFF)
		str = ft_wcharconv3and4(wc, 4);
	return (str);
}
