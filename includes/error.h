/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framel <framel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 09:44:04 by framel            #+#    #+#             */
/*   Updated: 2017/03/27 21:16:44 by rdestrue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define NB_ERR 16

char	*g_taberr[NB_ERR] =
{"> ./corewar [-s -v -z -dump nbr_cycles] [[-n number] champion1.cor] ...\n", \
	"Memory alloction fail\n", \
	"Any .cor file find to load\n", \
	"Open failure\n", \
	"Read failure\n", \
	"Corrupted file, invalid magic number\n", \
	"Argument in not an integer\n", \
	"Unable to read string\n", \
	"Floating point exception\n", \
	"Option -d need an integer\n", \
	"Invalid argument\n", \
	"Option -n need an integer\n", \
	"Id number is attribut several times\n", \
	"Too many files to load\n", \
	"Argument is too large to be in a signed integer\n", \
	"Champion too big\n"};

#endif
