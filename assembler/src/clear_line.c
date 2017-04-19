/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudra <hboudra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 13:39:19 by hboudra           #+#    #+#             */
/*   Updated: 2017/03/28 16:57:36 by framel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			wordnb(char *str)
{
	int	nb;

	nb = 0;
	if (!str)
		return (0);
	while (*str)
	{
		while (*str && ft_strchr(" \t", *str))
			str++;
		if (*str)
		{
			nb++;
			while (*str && !ft_strchr(" \t", *str))
				str++;
		}
	}
	return (nb);
}

static int	check_blank(char *str)
{
	while (str && *str && ft_strchr(" \t", *str))
		str++;
	if (!*str)
		return (1);
	return (0);
}

static int	gt_wordlen(char *str)
{
	int	i;

	i = 0;
	while (str && *str && !ft_strchr(" \t", *str))
	{
		i++;
		str++;
	}
	return (i);
}

static int	get_len(char *str, int nb)
{
	int		len;

	len = 0;
	while (str && *str)
	{
		if (!ft_strchr(" \t", *str))
			nb++;
		str++;
	}
	return (len + nb - 1);
}

char		*clear_line(char *str)
{
	int		len;
	char	*new;
	int		nb_word;

	nb_word = wordnb(str);
	len = get_len(str, nb_word);
	if (check_blank(str))
		return (ft_strdup(""));
	if (!(new = ft_strnew(len)))
		return (NULL);
	while (nb_word)
	{
		while (str && *str && ft_strchr(" \t", *str))
			str++;
		if (*str)
			ft_strncat(new, str, gt_wordlen(str));
		str += gt_wordlen(str);
		nb_word--;
		if (nb_word)
			ft_strcat(new, " ");
	}
	return (new);
}
