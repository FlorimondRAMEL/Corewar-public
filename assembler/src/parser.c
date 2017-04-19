/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudra <hboudra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 16:30:30 by hboudra           #+#    #+#             */
/*   Updated: 2017/03/28 18:37:20 by framel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "asm.h"
#include <stdlib.h>

int				parser(t_glob *glob, t_header *header, char *src)
{
	uint8_t		fd;

	if ((fd = open(src, O_RDONLY)) < 0)
		return (OPEN);
	name_retrieve(fd, header);
	comment_retrieve(fd, header);
	instructions(fd, glob);
	push_back(&glob->list, NULL);
	replace_label_char(glob);
	if (check(*glob))
		error(BAD_PARAMETRES);
	return (TRUE);
}
