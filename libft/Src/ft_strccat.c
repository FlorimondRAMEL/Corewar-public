/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strccat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framel <framel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 17:26:30 by framel            #+#    #+#             */
/*   Updated: 2017/03/27 17:27:01 by framel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Copie s2 (jusqu'au caractere c ou '\0' si c n'est pas present.) a la fin de
** s1 en ecrasant le caractere null de s1. Un caractere null est ecrit a la fin
** de s1.
*/

char	*ft_strccat(char *s1, const char *s2, char c)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (s1[j] != '\0')
		j++;
	while (s2[i] != c)
	{
		s1[j] = s2[i];
		i++;
		j++;
		if (s2[i] == '\0')
			break ;
	}
	s1[j] = '\0';
	return (s1);
}
