/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 10:11:25 by gcollet           #+#    #+#             */
/*   Updated: 2021/06/26 18:50:54 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdio.h>
# include <unistd.h>
# include <wctype.h>
# include <limits.h>

typedef struct s_s
{
	const char	*format;
	int			minus;
	int			zero;
	int			precision;
	int			width;
	int			w_asterisk;
	int			p_asterisk;
	int			ret;
	int			digit;
	int			temp;
	int			len;
	int			plus;
	int			space;
	int			sharp;
	long long	i;
	char		*ptr;
	int			l;
}		t_s;

t_s		ft_initialize_flag(t_s s);
t_s		ft_check(t_s s);
t_s		ft_check2(t_s s);
t_s		ft_check_bonus(t_s s);
t_s		ft_check_length(t_s s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlen(const char *s);
char	*ft_convert(unsigned long num, int base, int maj);
int		ft_putstr(char *s, int ret);
int		ft_putchar(char c, int ret);
int		ft_printf(const char *format, ...);
t_s		ft_print_text(t_s s);
t_s		ft_format(va_list ap, t_s s);
t_s		ft_format_l(va_list ap, t_s s);
t_s		ft_asterisk(va_list ap, t_s s);
int		is_a_conversion_specifier(t_s s);
int		ft_print_dori(long i, t_s s);
t_s		ft_print_dori1(t_s s);
t_s		ft_print_dori2(t_s s);
t_s		ft_print_dori3(t_s s);
t_s		ft_print_dori4(t_s s);
t_s		ft_print_dori5(t_s s);
t_s		ft_negative(t_s s);
int		ft_digit(int i);
int		ft_print_c(char c, t_s s);
int		ft_print_s(char *ptr, t_s s);
t_s		ft_print_s1(t_s s);
t_s		ft_print_s2(t_s s);
int		ft_print_p(char *ptr, t_s s);
int		ft_print_uint(char *ptr, t_s s);
t_s		ft_print_uint1(t_s s);
t_s		ft_print_uint2(t_s s);
int		ft_atoi(const char *nptr);

#endif