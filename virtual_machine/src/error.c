/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framel <framel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 09:44:50 by framel            #+#    #+#             */
/*   Updated: 2017/03/28 23:44:03 by rdestrue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "error.h"

uint8_t	ft_error_file(TYPE n)
{
	if (n == 0)
		return (ft_error(NULL, INVALFILE));
	if (n == INT_MAX)
		return (ft_error(NULL, ARGERR));
	if (n > MAX_PLAYERS)
		return (ft_error(NULL, TOOMANY));
	else
		return (FALSE);
}

uint8_t	ft_error(char *str, uint8_t err)
{
	write(2, "corewar: ", 9);
	if (str)
	{
		write(2, str, ft_strlen(str));
		write(2, ": ", 2);
	}
	write(2, g_taberr[err], ft_strlen(g_taberr[err]));
	return (FALSE);
}
