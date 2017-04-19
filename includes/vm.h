/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framel <framel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 05:31:58 by framel            #+#    #+#             */
/*   Updated: 2017/03/28 22:37:03 by rdestrue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "op.h"
# include "libft.h"
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>

# define SUCCESS 			0
# define FAILURE 			-1
# define TRUE 				1
# define FALSE 				0

# define HEXA(x) 			"0123456789abcdef"[x]
# define TYPE 				uint32_t
# define TYPE_MAX           UINT_MAX
# define TYPESIZE 			32

# define SUCCESS 			0
# define FAILURE 			-1
# define TRUE 				1
# define FALSE 				0

# define NOFILE 			0
# define MALLOCERR 			1
# define INVALFILE 			2
# define OPENERR 			3
# define READERR 			4
# define FILERR 			5
# define INTERR 			6
# define STRERR 			7
# define DIVERR 			8
# define DUMPERR 			9
# define ARGERR 			10
# define IDERR 				11
# define IDDUP 				12
# define TOOMANY 			13
# define TOOLARGE 			14
# define TOOBIG 			15

# define PARAM_1			192
# define PARAM_2			48
# define PARAM_3			12
# define INSTRUCTIONS_NB	16

/*
**	TYPEDEF
*/

typedef struct		s_file
{
	t_header		h;
	uint8_t			*p;
	TYPE			*n;
}					t_file;

typedef struct		s_data_prog
{
	int				parent;
	int				nb;
	int				reg[REG_NUMBER];
	unsigned short	pc;
	unsigned char	carry;
	unsigned int	next_run_cycle;
	unsigned char	next_instr;
	int				last_live;
	char			*name;
}					t_data_prog;

typedef struct		s_env
{
	uint8_t			mem[MEM_SIZE];
	uint32_t		nb_usr;
	uint32_t		cycle;
	uint32_t		max_process_nb;
	uint8_t			nb_checks;
	uint32_t		live_counter;
	int32_t			current_winner;
	int32_t			nb_cycles_to_die;
	uint32_t		next_check;
	uint8_t			verbose;
	uint8_t			silent;
	int8_t			zaz_opt;
	uint32_t		dump;
}					t_env;

typedef struct		s_op
{
	char			*instr_abbrev;
	char			nb_par;
	t_arg_type		par_types[3];
	char			instruction_nb;
	short			nb_cycles;
	char			*instr_name;
	char			opcode;
	char			ind_dir;
}					t_op;

/*
** Global Variables
*/

extern				t_op g_op_tab[17];

/*
** option
*/

TYPE				*ft_parseint(char ***argv);
uint8_t				ft_getarg(t_file *f, char **argv, TYPE n, t_env *e);
TYPE				ft_atoint(char *str, TYPE *nb);

/*
** mem.c
*/

void				initialise(t_env *e, t_data_prog *d, t_file *f, TYPE n);
void				init_env(t_env *e, TYPE n);

/*
** run.c
*/

uint8_t				ft_run(t_file *f, TYPE n, t_env *e);

/*
** tools.c
*/

TYPE				rev_endian(uint32_t octets);
TYPE				ft_divsup(TYPE n, TYPE d);
uint8_t				isstreq(char *s1, char *s2);
uint8_t				ft_isext(char *file, char *ext);

/*
** tools2.c
*/

uint8_t				ft_isint(char *str);
char				*ft_inttoa(TYPE nb);
TYPE				ft_nbrlen(TYPE nb);

/*
** error.c
*/

uint8_t				ft_error(char *str, uint8_t err);
uint8_t				ft_error_file(TYPE n);

/*
** test.c
*/

char				ft_test(t_env *env, unsigned short pc, unsigned char ocp, \
					unsigned char nb_instr);

/*
** print_memory.c
*/

void				print_memory(const void *addr, size_t size);

/*
** battle.c
*/

int					ft_launch_battle(t_data_prog **data_prog, t_env *env);

/*
** instr_args.c
*/

int					retrieve_ind_val(t_data_prog *data_prog, t_env *env, \
					short ind);
int					retrieve_param(t_data_prog *d_p, t_env *env, \
					unsigned char *o_cnt, unsigned int nb_p);
int					retrieve_param_nomod(t_data_prog *d_p, t_env *env, \
					unsigned char *o_cnt, unsigned int nb_p);
short				retrieve_dir_index(t_data_prog *data_prog, t_env *env, \
					unsigned char *oct_cnt, unsigned int nb_p);
char				ocp_value(unsigned char ocp, char nb_param, \
					char dir_nb_octets);

/*
** live_ld_st.c
*/

void				ft_write_to_mem(t_env *env, short p2, int reg_val);
int					do_live(t_data_prog **data_p, int i, t_env *env);
int					do_ld(t_data_prog **data_prog, int i, t_env *env);
int					do_st(t_data_prog **data_prog, int i, t_env *env);

/*
** add_and.c
*/

int					do_add(t_data_prog **data_p, int i, t_env *env);
int					do_sub(t_data_prog **data_p, int i, t_env *env);
int					do_and(t_data_prog **data_p, int i, t_env *env);
int					do_or(t_data_prog **data_p, int i, t_env *env);
int					do_xor(t_data_prog **data_p, int i, t_env *env);

/*
** zjmp_ind_long.c
*/

int					do_zjmp(t_data_prog **data_prog, int i, t_env *env);
int					do_ldi(t_data_prog **d_p, int i, t_env *env);
int					do_sti(t_data_prog **data_p, int i, t_env *env);
int					do_lld(t_data_prog **data_prog, int i, t_env *env);
int					do_lldi(t_data_prog **data_p, int i, t_env *env);

/*
** fork_aff.c
*/

int					do_fork(t_data_prog **d_p, int i, t_env *env);
int					do_lfork(t_data_prog **d_p, int i, t_env *env);
int					do_aff(t_data_prog **data_p, int i, t_env *env);

/*
** run_instr.c
*/

int					ft_run_cycle(t_data_prog **data_prog, t_env *env);
void				ft_init_run_cycle(t_data_prog *data_prog, t_env *env);
void				init_instructions(void);
int					(*g_fct_ptr[INSTRUCTIONS_NB])(t_data_prog **data_prog, \
					int i, t_env *env);

#endif
