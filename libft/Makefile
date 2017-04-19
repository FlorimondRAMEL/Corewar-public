# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rdestrue <rdestrue@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/13 11:48:18 by rdestrue          #+#    #+#              #
#    Updated: 2017/03/28 18:25:46 by framel           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

INCLUDES_PATH = ./Includes

SRC_PATH = ./Src/

SRC = ft_atoi.c ft_atoi_max.c ft_bzero.c ft_char_spec.c ft_date_spec.c \
	ft_dealing_with_format.c ft_fcts_array.c ft_ftoa_base.c ft_hex_spec.c \
	ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isnumber.c \
	ft_isprint.c ft_itoa.c ft_itoa_base.c ft_itoa_base_max.c ft_itoa_base_u.c \
	ft_itoa_base_umax.c ft_list_reverse.c ft_list_size.c ft_lst_cat.c \
	ft_lst_cpy.c ft_lst_free.c ft_lst_free_one.c ft_lst_last.c ft_lst_nth.c \
	ft_lstadd.c ft_lstaddend.c ft_lstaddn_or_end.c ft_lstdel.c ft_lstdelone.c \
	ft_lstfold.c ft_lstiter.c ft_lstmap.c ft_lstnew.c ft_max.c ft_memalloc.c \
	ft_memccpy.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memdel.c ft_memmove.c \
	ft_memset.c ft_min.c ft_power.c ft_power_fmax.c ft_power_max.c \
	ft_printf.c ft_putchar.c ft_putchar_fd.c ft_putendl.c ft_putendl_fd.c \
	ft_putnbr.c ft_putnbr_fd.c ft_putnbr_max.c ft_putstr.c ft_putstr_fd.c \
	ft_signed_spec.c ft_str_spec.c ft_str_tolower.c ft_str_toupper.c \
	ft_strcat.c ft_strchr.c ft_strclr.c ft_strcmp.c ft_strcpy.c ft_strdel.c \
	ft_strdup.c ft_strequ.c ft_striter.c ft_striteri.c ft_strjoin.c \
	ft_strlcat.c ft_strlen.c ft_strmap.c ft_strmapi.c ft_strncat.c \
	ft_strncmp.c ft_strncpy.c ft_strnequ.c ft_strnew.c ft_strnstr.c \
	ft_strrchr.c ft_strrev.c ft_strsplit.c ft_strsplit_list.c ft_strstr.c \
	ft_strsub.c ft_strtrim.c ft_tolower.c ft_toupper.c ft_unsigned_spec.c \
	ft_wcharconv.c ft_width_and_prec.c ft_wstrlen.c get_next_line.c \
	ft_strccat.c ft_isspace.c ft_strndup.c ft_fprintf.c percent_c.c \
	percent_d.c percent_s.c tools.c ft_ltoa.c ft_strjoincat.c

OBJ_PATH = ./Obj/

OBJ = $(SRC:%.c=$(OBJ_PATH)/%.o)

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(INCLUDES_PATH)
	@mkdir -p $(OBJ_PATH)
	@gcc $(FLAGS) -I $(INCLUDES_PATH) -o $@ -c $<

clean:
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -f $(NAME)

re: fclean all
