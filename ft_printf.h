/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 10:11:25 by gcollet           #+#    #+#             */
/*   Updated: 2021/06/22 16:14:51 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdio.h>
# include "libft/libft.h"

/* # include "libft/ft_atoi.c"
# include "libft/ft_strlcpy.c"
# include "libft/ft_strlen.c"
#include <limits.h> */

typedef struct s_flags
{
	int	minus;
	int zero;
	int	precision;
	int	width;
	int w_asterisk;
	int p_asterisk;

}		t_flags;

t_flags	ft_initialize_flag(t_flags flags);
t_flags	ft_check(const char *format, t_flags flags);
char *ft_convert(unsigned long num, int base, int maj);
int	ft_putstr(char *s, int ret);
int	ft_putchar(char c, int ret);
int ft_printf(const char *format, ...);
int is_a_conversion_specifier(const char *format);
int ft_print_dori(long i, int ret, t_flags flags);
int ft_print_c(char c, int ret, t_flags flags);
int ft_print_s(char *ptr, int ret, t_flags flags);
int ft_print_p(char *ptr, int ret, t_flags flags);
int ft_digit(int digit, int i);
int ft_print_x(char *ptr, int ret, t_flags flags);
int ft_print_u(char *ptr, int ret, t_flags flags);


#endif