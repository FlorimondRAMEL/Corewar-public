/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestrue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 17:52:27 by rdestrue          #+#    #+#             */
/*   Updated: 2017/03/27 12:16:17 by rdestrue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		retrieve_ind_val(t_data_prog *data_prog, t_env *env, short ind)
{
	int	param;

	ind = (*data_prog).pc + ind;
	if (ind < 0)
		ind = MEM_SIZE + ind % MEM_SIZE;
	param = ((*env).mem[ind % MEM_SIZE] << 24) + \
			((*env).mem[(ind + 1) % MEM_SIZE] << 16) + \
			((*env).mem[(ind + 2) % MEM_SIZE] << 8) + \
			(*env).mem[(ind + 3) % MEM_SIZE];
	return (param);
}

int		retrieve_param(t_data_prog *d_p, t_env *env, \
		unsigned char *o_cnt, unsigned int nb_p)
{
	int		par;
	char	shft;

	shft = (nb_p == PARAM_1) ? 6 : 4;
	if (nb_p == PARAM_3)
		shft = 2;
	par = (*env).mem[((*d_p).pc + *o_cnt) % MEM_SIZE];
	(*o_cnt)++;
	if ((((*env).mem[((*d_p).pc + 1) % MEM_SIZE] & nb_p) >> shft) > REG_CODE)
	{
		par = (par << 8) + (*env).mem[((*d_p).pc + *o_cnt) % MEM_SIZE];
		(*o_cnt)++;
		if ((((*env).mem[((*d_p).pc + 1) % MEM_SIZE] & nb_p) >> shft) == \
			DIR_CODE)
		{
			par = (par << 8) + (*env).mem[((*d_p).pc + *o_cnt) % MEM_SIZE];
			par = (par << 8) + (*env).mem[((*d_p).pc + *o_cnt + 1) % MEM_SIZE];
			*o_cnt = *o_cnt + 2;
		}
		else
			par = retrieve_ind_val(d_p, env, (short)par % IDX_MOD);
	}
	else
		par = (*d_p).reg[par - 1];
	return (par);
}

int		retrieve_param_nomod(t_data_prog *d_p, t_env *env, \
		unsigned char *o_cnt, unsigned int nb_p)
{
	int		par;
	char	shft;

	shft = (nb_p == PARAM_1) ? 6 : 4;
	if (nb_p == PARAM_3)
		shft = 2;
	par = (*env).mem[((*d_p).pc + *o_cnt) % MEM_SIZE];
	(*o_cnt)++;
	if ((((*env).mem[((*d_p).pc + 1) % MEM_SIZE] & nb_p) >> shft) > REG_CODE)
	{
		par = (par << 8) + (*env).mem[((*d_p).pc + *o_cnt) % MEM_SIZE];
		(*o_cnt)++;
		if ((((*env).mem[((*d_p).pc + 1) % MEM_SIZE] & nb_p) >> shft) == \
			DIR_CODE)
		{
			par = (par << 8) + (*env).mem[((*d_p).pc + *o_cnt) % MEM_SIZE];
			par = (par << 8) + (*env).mem[((*d_p).pc + *o_cnt + 1) % MEM_SIZE];
			*o_cnt = *o_cnt + 2;
		}
		else
			par = retrieve_ind_val(d_p, env, par);
	}
	else
		par = (*d_p).reg[par - 1];
	return (par);
}

short	retrieve_dir_index(t_data_prog *data_prog, t_env *env, \
		unsigned char *oct_cnt, unsigned int nb_p)
{
	short	ind;
	char	shift;

	shift = (nb_p == PARAM_1) ? 6 : 4;
	if (nb_p == PARAM_3)
		shift = 2;
	ind = (*env).mem[((*data_prog).pc + *oct_cnt) % MEM_SIZE];
	(*oct_cnt)++;
	ind = (ind << 8) + (*env).mem[((*data_prog).pc + *oct_cnt) % MEM_SIZE];
	(*oct_cnt)++;
	return (ind);
}

char	ocp_value(unsigned char ocp, char nb_param, char dir_nb_octets)
{
	char	nb_octets;

	if (ocp == 0)
		return (0);
	nb_octets = 0;
	if (((ocp & PARAM_1) >> 6) == REG_CODE)
		nb_octets = nb_octets + 1;
	else if (((ocp & PARAM_1) >> 6) == IND_CODE)
		nb_octets = nb_octets + 2;
	else if (((ocp & PARAM_1) >> 6) == DIR_CODE)
		nb_octets = nb_octets + dir_nb_octets;
	if (nb_param > 1 && ((ocp & PARAM_2) >> 4) == REG_CODE)
		nb_octets = nb_octets + 1;
	else if (nb_param > 1 && ((ocp & PARAM_2) >> 4) == IND_CODE)
		nb_octets = nb_octets + 2;
	else if (nb_param > 1 && ((ocp & PARAM_2) >> 4) == DIR_CODE)
		nb_octets = nb_octets + dir_nb_octets;
	if (nb_param == 3 && ((ocp & PARAM_3) >> 2) == REG_CODE)
		nb_octets = nb_octets + 1;
	else if (nb_param == 3 && ((ocp & PARAM_3) >> 2) == IND_CODE)
		nb_octets = nb_octets + 2;
	else if (nb_param == 3 && ((ocp & PARAM_3) >> 2) == DIR_CODE)
		nb_octets = nb_octets + dir_nb_octets;
	return (nb_octets);
}
