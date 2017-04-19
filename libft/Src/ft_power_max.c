/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power_max.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestrue <rdestrue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 23:03:26 by rdestrue          #+#    #+#             */
/*   Updated: 2016/08/13 16:11:31 by rdestrue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

intmax_t	ft_power_max(intmax_t nb, int exponent)
{
	intmax_t result;

	result = 1;
	if (exponent < 0)
		return (0);
	while (exponent > 0)
	{
		result = result * nb;
		exponent = exponent - 1;
	}
	return (result);
}
