/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudra <hboudra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 15:10:06 by hboudra           #+#    #+#             */
/*   Updated: 2017/03/28 18:43:24 by framel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "libft.h"
# include <stdbool.h>
# include <fcntl.h>
# include <limits.h>

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)

# define COREWAR_EXEC_MAGIC		0xea83f3
# define BLANK_ZONE				0000
# define COMMENT_CHAR			'#'
# define COMMENT				"/* :Prog_name:"
# define NAME_CMD_STRING		".name"
# define COMMENT_CMD_STRING		".comment"
# define COMMENT_CHARS			";#"
# define LABEL_END				':'
# define LABEL_CHARS			"abcdefghijklmnopqrstuvwxyz_0123456789"
# define LABEL_CHAR				':'
# define DIRECT_CHAR			'%'
# define T_REG					1
# define T_DIR					2
# define T_IND					4
# define T_LAB					8
# define MAX_LONG				"9223372036854775807"
# define L_STR(x) ((t_label*)(x->content))->str

# define LIVE					0x01
# define LD						0x02
# define ST						0x03
# define ADD					0x04
# define SUB					0x05
# define AND					0x06
# define OR						0x07
# define XOR					0x08
# define ZJUMP					0x09
# define LDI					0x0a
# define STI					0x0b
# define FORK					0x0c
# define LLD					0x0d
# define LLDI					0x0e
# define LFORK					0x0f
# define AFF					0x10

# define ERROR				-1
# define FALSE				0
# define TRUE				1
# define NAME				2
# define OPEN				3
# define MALLOC				4
# define NAME_2				5
# define NAME_3				6
# define COM				7
# define BAD_LABEL			8
# define BAD_INSTRUCTION 	9
# define BAD_ARGUMENT		10
# define BAD_NUMBER_PARAM	11
# define NO_INSTRUCTIONS	12
# define BAD_PARAMETRES		13
# define CREATING_FILE		14
# define BAD_LABEL_FORMAT	15

typedef struct		s_op
{
	char			*instruction_name;
	uint8_t			nb_arg;
	uint8_t			arg_value[4];
	uint8_t			opcode;
	uint16_t		n_cycle;
	char			*desc_instr;
	bool			carry;
	bool			dir_indir;
}					t_op;

typedef struct		s_header
{
	unsigned int	magic;
	unsigned int	prog_size;
	char			comment[COMMENT_LENGTH + 1];
	char			prog_name[PROG_NAME_LENGTH + 1];
}					t_header;

typedef struct		s_info
{
	char			**param;
	char			opcode;
	unsigned char	ocp;
	struct s_info	*next;
}					t_info;

typedef struct		s_label
{
	char			*str;
	int				n_inst;
}					t_label;

typedef struct		s_glob
{
	t_list			*label;
	t_info			*list;
}					t_glob;

static t_op			g_op_tab[] =
{
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG},\
		6, 6, "et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},\
		7, 6, "ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},\
		8, 6, "ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},\
		10, 25, "load index", 1, 1},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG},\
		11, 25, "store index", 1, 1},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},\
		14, 50, "long load index", 1, 1},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0},
	{0, 0, {0}, 0, 0, 0, 0, 0}
};

int					name(char *name);
int					parser(t_glob *glob, t_header *header, char *src);
int					skip(char *str);
int					is_comment(char *str);
int					count_char(char *str, char c);
int					is_reg(char *str);
int					is_direct(char *str);
int					is_ind(char *str);
int					parse_info(t_glob *glob, char *line);
int					wordnb(char *str);
int					is_reg(char *str);
int					is_direct(char *str);
int					is_ind(char *str);
int					check_6(t_info *info);
int					check_5(t_glob glob, t_info *info);
int					check(t_glob glob);
int					create(char *arg, char **file);
int					count_byte_inst(t_info *info);
int					invert_2(int i);
int					invert_4(int i);
long				get_nbr(const char *str);
int					get_label_val(t_info *info, t_glob glob, int i);
long				invert_8(long i);
char				ocp_calc(t_info *info);
char				*check_label(char *line);
char				*clear_line(char *str);
bool				check_label_2(char *label);
t_info				*new_info(void);
void				name_retrieve(int fd, t_header *header);
void				parse_label(t_glob *glob, char *line, int i, \
								bool *label_exist);
void				error(int err);
void				check_quote(char *str);
void				comment_retrieve(int fd, t_header *header);
void				instructions(int fd, t_glob *glob);
void				push_back(t_info **lst, t_info *new);
void				replace_line(char **line);
void				replace_label_char(t_glob *glob);
void				write_file(int fd, t_header header, t_glob glob);
void				write_nb_inst(t_info *info, int fd);
void				write_param(int fd, t_glob glob);
void				write_reg(int fd, int i, t_info *info);
void				write_dir(int fd, int i, t_info *info, t_glob glob);
void				write_ind(int fd, int i, t_info *info, t_glob glob);

#endif
