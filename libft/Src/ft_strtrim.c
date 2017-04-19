/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestrue <rdestrue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/20 20:04:54 by rdestrue          #+#    #+#             */
/*   Updated: 2016/01/18 12:30:02 by rdestrue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	int		i;
	int		j;
	size_t	len;
	char	*str;

	i = 0;
	while (s[i] == '\n' || s[i] == '\t' || s[i] == ' ')
		i++;
	len = ft_strlen(s);
	if (i == (int)len)
		return (ft_strnew(0));
	while (s[len - 1] == '\n' || s[len - 1] == '\t' || s[len - 1] == ' ')
		len--;
	len = len - i;
	str = ft_strnew(len);
	if (str == NULL)
		return (str);
	j = len;
	while (j > 0)
	{
		str[len - j] = s[i];
		i++;
		j--;
	}
	return (str);
}
