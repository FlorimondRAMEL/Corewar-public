/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudra <hboudra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 15:06:03 by hboudra           #+#    #+#             */
/*   Updated: 2017/03/28 16:58:22 by framel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

long	get_nbr(const char *str)
{
	long	nb;
	long	signe;
	int		len;

	nb = 0;
	signe = 1;
	while (str && *str && ft_strchr(" \t\n\v\r\f", *str))
		str++;
	if (str && *str == '-')
	{
		signe = -1;
		str++;
	}
	if ((len = ft_strlen(str)) > (int)ft_strlen(MAX_LONG) && signe == 1)
		return (LONG_MAX);
	else if (len > (int)ft_strlen(MAX_LONG) && signe == -1)
		return (0);
	while (str && ft_isdigit(*str))
		nb = nb * 10 + *str++ - '0';
	if (len == (int)ft_strlen(MAX_LONG) && nb < 0 && signe == 1)
		return (LONG_MAX);
	else if (len == (int)ft_strlen(MAX_LONG) && nb < 0 && signe == -1)
		return (0);
	return (nb * signe);
}

void	check_quote(char *str)
{
	int		i;
	int		quotes;
	char	c;

	i = 0;
	quotes = 0;
	while (str[i] && quotes < 2)
	{
		if (str[i] == '\"')
			quotes++;
		i++;
	}
	i += skip(str + i);
	c = str[i];
	if (c != '\0' && c != '\"' && c != COMMENT_CHAR && c != ';')
		error(NAME_2);
}

int		name(char *name)
{
	int	i;

	i = 0;
	while (name[i])
		i++;
	if (name[i - 1] != 's' || name[i - 2] != '.')
		return (ERROR);
	return (TRUE);
}
