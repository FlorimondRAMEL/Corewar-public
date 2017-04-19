/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/04 11:22:08 by exam              #+#    #+#             */
/*   Updated: 2017/03/28 18:46:03 by rdestrue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "vm.h"

void				ft_puthexa(unsigned char octet)
{
	char			*hexa_str;

	hexa_str = "0123456789abcdef";
	if (octet >= 16)
	{
		write(1, &(hexa_str[octet / 16]), 1);
		write(1, &(hexa_str[octet % 16]), 1);
	}
	else
	{
		write(1, "0", 1);
		write(1, &(hexa_str[octet]), 1);
	}
}

void				print_memory(const void *addr, size_t size)
{
	unsigned char	*str;
	int				i;

	str = (unsigned char *)addr;
	i = 0;
	ft_printf("0x0000 : ", i);
	while (i < (int)size)
	{
		ft_puthexa(str[i]);
		i++;
		if (i % 32 == 0 && i != (int)size)
		{
			write(1, "\n", 1);
			ft_printf("%#.4x : ", i);
		}
		else if (i != (int)size)
			write(1, " ", 1);
	}
	write(1, "\n", 1);
}
