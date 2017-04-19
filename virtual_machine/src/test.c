/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestrue <rdestrue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 12:46:18 by rdestrue          #+#    #+#             */
/*   Updated: 2017/03/28 13:19:17 by rdestrue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

char	ft_reg_number(char par, t_env *env, unsigned short pc)
{
	if (par == REG_CODE && ((*env).mem[pc % MEM_SIZE] <= 0 || \
		(*env).mem[pc % MEM_SIZE] > REG_NUMBER))
		return (-1);
	return (0);
}

char	ft_nb_octets(char par, unsigned char nb_instr)
{
	if (par == REG_CODE)
		return (1);
	else if (par == T_IND)
		return (2);
	else if (par == DIR_CODE && g_op_tab[nb_instr].ind_dir)
		return (2);
	else if (par == DIR_CODE && !g_op_tab[nb_instr].ind_dir)
		return (4);
	else
		return (0);
}

char	ft_test(t_env *env, unsigned short pc, unsigned char ocp, \
		unsigned char nb_instr)
{
	char			par1;
	char			par2;
	char			par3;

	if (nb_instr == 0 || nb_instr == 8 || nb_instr == 11 || nb_instr == 14)
		return (0);
	par1 = (((ocp & PARAM_1) >> 6)) == IND_CODE ? T_IND : (ocp & PARAM_1) >> 6;
	par2 = (((ocp & PARAM_2) >> 4)) == IND_CODE ? T_IND : (ocp & PARAM_2) >> 4;
	par3 = (((ocp & PARAM_3) >> 2)) == IND_CODE ? T_IND : (ocp & PARAM_3) >> 2;
	if ((par1 & g_op_tab[nb_instr].par_types[0]) == 0 || \
		(par2 & g_op_tab[nb_instr].par_types[1]) == 0 || \
		(g_op_tab[nb_instr].nb_par == 3 && \
		(par3 & g_op_tab[nb_instr].par_types[2]) == 0))
		return (-1);
	par1 = ft_nb_octets(par1, nb_instr);
	par2 = ft_nb_octets(par2, nb_instr);
	par3 = ft_nb_octets(par3, nb_instr);
	if (ft_reg_number(par1, env, pc + 2) == -1 || \
		ft_reg_number(par2, env, pc + 2 + par1) == -1 || \
		(g_op_tab[nb_instr].nb_par == 3 && \
		ft_reg_number(par3, env, pc + 2 + par1 + par2) == -1))
		return (-1);
	return (0);
}
