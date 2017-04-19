/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudra <hboudra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 15:06:25 by hboudra           #+#    #+#             */
/*   Updated: 2017/03/28 17:09:48 by framel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "asm.h"
#include "libft.h"

static void	error_next(int err)
{
	if (err == BAD_ARGUMENT)
		ft_putendl_fd("Wrong argument in instruction", 2);
	else if (err == BAD_INSTRUCTION)
		ft_putendl_fd("Instruction is invalid", 2);
	else if (err == BAD_NUMBER_PARAM)
		ft_putendl_fd("Too much or not enough argument in instruction", 2);
	else if (err == NO_INSTRUCTIONS)
		ft_putendl_fd("No instruction in this file", 2);
	else if (err == CREATING_FILE)
		ft_putendl_fd("File Creation Failed", 2);
	else if (err == BAD_LABEL_FORMAT)
		ft_putendl_fd("A label is incorrrect", 2);
	else
		ft_putendl_fd("error", 2);
}

void		error(int err)
{
	if (err == NAME)
		ft_putendl_fd("File must have the extension .s", 2);
	else if (err == OPEN)
		ft_putendl_fd("Impossible to open this file", 2);
	else if (err == MALLOC)
		ft_putendl_fd("A memory allocation has failed", 2);
	else if (err == NAME_2)
		ft_putendl_fd("Error in program name", 2);
	else if (err == NAME_3)
		ft_putendl_fd("Program name is too long (128 letter MAX)", 2);
	else if (err == COM)
		ft_putendl_fd("Champion's comment is invalid", 2);
	else if (err == BAD_LABEL)
		ft_putendl_fd("A label is invalid", 2);
	else
		error_next(err);
	exit(3);
}
