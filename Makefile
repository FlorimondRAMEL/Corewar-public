#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: framel <framel@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/27 13:26:24 by framel            #+#    #+#              #
#    Updated: 2017/03/27 21:47:03 by rdestrue         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

CC = gcc

CFLAGS = -Wall -Werror -Wextra

LIBFT_PATH = ./libft

LIBFT = $(LIBFT_PATH)/libft.a

ASM_NAME = asm

ASM_SRC = check.c check_1.c check_param.c clear_line.c comment.c count_byte.c \
	create_n_set_file.c error.c functions.c instructions.c invert.c label.c \
	label_val.c main.c name.c ocp.c parse_info.c parser.c t_info.c tools.c \
	write_inst.c write_param.c write_param_1.c

ASM_SRC_PATH = ./assembler/src

ASM_OBJ_PATH = ./assembler/obj

ASM_OBJ = $(ASM_SRC:%.c=$(ASM_OBJ_PATH)/%.o)

CW_NAME = corewar

CW_SRC = error.c main.c mem.c op.c option.c print_memory.c run.c test.c \
		 tools.c tools2.c add_and.c battle.c fork_aff.c instr_args.c \
		 run_instr.c live_ld_st.c zjmp_ind_long.c

CW_SRC_PATH = ./virtual_machine/src

CW_OBJ_PATH = ./virtual_machine/obj

CW_OBJ = $(CW_SRC:%.c=$(CW_OBJ_PATH)/%.o)

INC = ./includes

INC_LIBFT = ./libft/Includes

all: $(ASM_NAME) $(CW_NAME)

$(ASM_NAME): $(ASM_OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) -o $(ASM_NAME) $(ASM_OBJ) $(LIBFT)
	@echo "asm created"

$(ASM_OBJ_PATH)/%.o: $(ASM_SRC_PATH)/%.c $(INC) $(INC_LIBFT)
	@mkdir -p $(ASM_OBJ_PATH)
	@$(CC) $(CFLAGS) -o $@ -c $< -I $(INC) -I $(INC_LIBFT)

$(CW_NAME): $(CW_OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) -o $(CW_NAME) $(CW_OBJ) $(LIBFT)
	@echo "corewar created"

$(CW_OBJ_PATH)/%.o: $(CW_SRC_PATH)/%.c $(INC) $(INC_LIBFT)
	@mkdir -p $(CW_OBJ_PATH)
	@$(CC) $(CFLAGS) -o $@ -c $< -I $(INC) -I $(INC_LIBFT)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_PATH) all

clean:
	/bin/rm -rf $(ASM_OBJ_PATH)
	/bin/rm -rf $(CW_OBJ_PATH)
	@$(MAKE) -C $(LIBFT_PATH) clean

fclean: clean
	/bin/rm -rf $(ASM_NAME)
	/bin/rm -rf $(CW_NAME)
	@$(MAKE) -C $(LIBFT_PATH) fclean

re: fclean all
