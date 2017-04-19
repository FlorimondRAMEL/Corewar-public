/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestrue <rdestrue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 22:38:15 by rdestrue          #+#    #+#             */
/*   Updated: 2016/01/20 12:46:12 by rdestrue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *str)
{
	size_t	len;
	size_t	i;
	char	*rts;

	len = ft_strlen(str);
	rts = ft_strnew(len);
	if (rts == NULL)
		return (NULL);
	len--;
	i = 0;
	while (len > 0)
	{
		rts[len] = str[i];
		i++;
		len--;
	}
	rts[len] = str[i];
	return (rts);
}
