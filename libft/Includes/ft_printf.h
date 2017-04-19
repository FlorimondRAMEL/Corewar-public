/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestrue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/31 20:58:21 by rdestrue          #+#    #+#             */
/*   Updated: 2016/09/11 19:46:32 by rdestrue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"

# define DIESE 1
# define ZERO 2
# define MINUS 4
# define PLUS 8
# define SPACE 16
# define PREC 32
# define ONEH 64
# define ONEL 128
# define ONEJ 256
# define ONEZ 512
# define TWOH 1024
# define TWOL 2048

typedef	struct	s_format
{
	char		*ref_flags;
	char		*ref_spec;
	int			flg_md;
	int			width;
	int			prec;
	char		format;
}				t_format;

int				ft_s(t_format *param, va_list ap, intmax_t *cnt);
int				ft_d(t_format *param, va_list ap, intmax_t *cnt);
int				ft_u(t_format *param, va_list ap, intmax_t *cnt);
int				ft_o(t_format *param, va_list ap, intmax_t *cnt);
int				ft_b(t_format *param, va_list ap, intmax_t *cnt);
int				ft_x(t_format *param, va_list ap, intmax_t *cnt);
int				ft_bigx(t_format *param, va_list ap, intmax_t *cnt);
int				ft_p(t_format *param, va_list ap, intmax_t *cnt);
int				ft_c(t_format *param, va_list ap, intmax_t *cnt);
int				ft_n(t_format *param, va_list ap, intmax_t *cnt);
int				ft_k(t_format *param, va_list ap, intmax_t *cnt);
int				ft_f(t_format *param, va_list ap, intmax_t *cnt);
int				(*g_ft_fcts_ptr[14])(t_format *param, va_list ap, \
				intmax_t *cnt);
int				ft_percent(t_format *param, intmax_t *cnt);
void			ft_fcts_array(void);
char			*ft_unsigned_nb(t_format *param, va_list ap, int base);
int				ft_k_hour_suffixe(char *str, va_list ap);
char			*ft_nb_diese_plus_space(char *str, char c);
int				ft_handle_str(t_format *param, char *str, intmax_t *cnt);
char			*ft_wider_field(char *str, t_format *param);
char			*ft_nb_prec(char *str, t_format *param, char c);
int				ft_flags(const char **format, t_format *param);
int				ft_field_width(const char **format, t_format *param, va_list \
				ap);
int				ft_precision(const char **format, t_format *param, va_list ap);
int				ft_modifiers(const char **format, t_format *param);
int				ft_specifier(const char **format, t_format *param, va_list ap, \
				intmax_t *cnt);
int				ft_printf(const char *format, ...);

#endif
