/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 12:04:44 by gcollet           #+#    #+#             */
/*   Updated: 2021/07/06 14:08:12 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

t_s	ft_format(va_list ap, t_s s)
{
	if (*s.format == 'c')
		s.ret = ft_print_c(va_arg(ap, int), s);
	else if (*s.format == 'd' || *s.format == 'i')
		s.ret = ft_print_dori(va_arg(ap, int), s);
	else if (*s.format == 's')
		s.ret = ft_print_s(va_arg(ap, char *), s);
	else if (*s.format == 'p')
		s.ret = ft_print_p(ft_convert(va_arg(ap, unsigned long), 16, 0), s);
	else if (*s.format == 'u')
		s.ret = ft_print_uint(ft_convert(va_arg(ap, unsigned int), 10, 0), s);
	else if (*s.format == 'x')
		s.ret = ft_print_uint(ft_convert(va_arg(ap, unsigned int), 16, 0), s);
	else if (*s.format == 'X')
		s.ret = ft_print_uint(ft_convert(va_arg(ap, unsigned int), 16, 1), s);
	else if (*s.format == '%')
		s.ret = ft_print_c('%', s);
	else if (*s.format == 'n')
		*va_arg(ap, int *) = s.ret;
	else if (*s.format == 'f')
		s.ret = ft_print_f(va_arg(ap, double), s);
	else
		s.len = -1;
	return (s);
}

t_s	ft_format_l(va_list ap, t_s s)
{
	if (*s.format == 'c')
		s.ret = ft_print_wc(va_arg(ap, wint_t), s);
	else if (*s.format == 'd' || *s.format == 'i')
		s.ret = ft_print_dori(va_arg(ap, long), s);
	else if (*s.format == 's')
		s.ret = ft_print_ws(va_arg(ap, wchar_t *), s);
	else if (*s.format == 'p')
		s.ret = ft_print_p(ft_convert(va_arg(ap, unsigned long), 16, 0), s);
	else if (*s.format == 'u')
		s.ret = ft_print_uint(ft_convert(va_arg(ap, unsigned long), 10, 0), s);
	else if (*s.format == 'x')
		s.ret = ft_print_uint(ft_convert(va_arg(ap, unsigned long), 16, 0), s);
	else if (*s.format == 'X')
		s.ret = ft_print_uint(ft_convert(va_arg(ap, unsigned long), 16, 1), s);
	else if (*s.format == '%')
		s.ret = ft_print_c('%', s);
	else if (*s.format == 'n')
		*va_arg(ap, long *) = s.ret;
	else
	{
		s.len = -1;
		return (s);
	}
	return (s);
}

t_s	ft_format_ll(va_list ap, t_s s)
{
	if ((*s.format == 'c') || (*s.format == 's') || (*s.format == 'p')
		|| (*s.format == '%'))
		s = ft_format(ap, s);
	else if (*s.format == 'd' || *s.format == 'i')
		s.ret = ft_print_dori(va_arg(ap, long long), s);
	else if (*s.format == 'u')
		s.ret = ft_print_uint(ft_convert(va_arg(ap,
						unsigned long long), 10, 0), s);
	else if (*s.format == 'x')
		s.ret = ft_print_uint(ft_convert(va_arg(ap,
						unsigned long long), 16, 0), s);
	else if (*s.format == 'X')
		s.ret = ft_print_uint(ft_convert(va_arg(ap,
						unsigned long long), 16, 1), s);
	else if (*s.format == 'n')
		*va_arg(ap, long long *) = s.ret;
	else
	{
		s.len = -1;
		return (s);
	}
	return (s);
}

t_s	ft_format_h(va_list ap, t_s s)
{
	if ((*s.format == 'c') || (*s.format == 's') || (*s.format == 'p')
		|| (*s.format == '%'))
		s = ft_format(ap, s);
	else if (*s.format == 'd' || *s.format == 'i')
		s.ret = ft_print_dori((short)va_arg(ap, int), s);
	else if (*s.format == 'u')
		s.ret = ft_print_uint(ft_convert((unsigned short)va_arg(ap,
						unsigned int), 10, 0), s);
	else if (*s.format == 'x')
		s.ret = ft_print_uint(ft_convert((unsigned short)va_arg(ap,
						unsigned int), 16, 0), s);
	else if (*s.format == 'X')
		s.ret = ft_print_uint(ft_convert((unsigned short)va_arg(ap,
						unsigned int), 16, 1), s);
	else if (*s.format == 'n')
		*va_arg(ap, short *) = s.ret;
	else
	{
		s.len = -1;
		return (s);
	}
	return (s);
}

t_s	ft_format_hh(va_list ap, t_s s)
{
	if ((*s.format == 'c') || (*s.format == 's') || (*s.format == 'p')
		|| (*s.format == '%'))
		s = ft_format(ap, s);
	else if (*s.format == 'd' || *s.format == 'i')
		s.ret = ft_print_dori((char)va_arg(ap, int), s);
	else if (*s.format == 'u')
		s.ret = ft_print_uint(ft_convert((unsigned char)va_arg(ap,
						unsigned int), 10, 0), s);
	else if (*s.format == 'x')
		s.ret = ft_print_uint(ft_convert((unsigned char)va_arg(ap,
						unsigned int), 16, 0), s);
	else if (*s.format == 'X')
		s.ret = ft_print_uint(ft_convert((unsigned char)va_arg(ap,
						unsigned int), 16, 1), s);
	else if (*s.format == 'n')
		*va_arg(ap, char *) = s.ret;
	else
	{
		s.len = -1;
		return (s);
	}
	return (s);
}
