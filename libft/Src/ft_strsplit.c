/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestrue <rdestrue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/20 20:03:20 by rdestrue          #+#    #+#             */
/*   Updated: 2016/10/30 01:10:38 by rdestrue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_split(char **strtab, char const *s, char c)
{
	int	i;
	int j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (s[k])
	{
		while (s[k] && s[k] == c)
			k++;
		if (s[k])
			j = k;
		while (s[k] && s[k] != c)
			k++;
		strtab[i] = ft_strsub(s, j, k - j);
		if (strtab[i] == NULL)
			return (i);
		i++;
	}
	return (0);
}

static int	ft_words_count(char const *s, char c)
{
	int counter;
	int	k;

	counter = 0;
	k = 0;
	while (s[k])
	{
		while (s[k] && s[k] == c)
			k++;
		if (s[k])
			counter++;
		while (s[k] && s[k] != c)
			k++;
	}
	return (counter);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**strtab;
	int		i;
	int		words_nb;

	if (s == NULL)
		return (NULL);
	words_nb = ft_words_count(s, c);
	strtab = (char **)ft_memalloc(sizeof(*strtab) * (words_nb + 1));
	if (strtab == NULL)
		return (NULL);
	strtab[words_nb] = NULL;
	words_nb = ft_split(strtab, s, c);
	if (words_nb)
	{
		i = 0;
		while (i < words_nb)
		{
			free(strtab[i]);
			i++;
		}
		free(strtab);
		return (NULL);
	}
	return (strtab);
}
