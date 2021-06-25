/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 12:04:44 by gcollet           #+#    #+#             */
/*   Updated: 2021/06/25 12:11:05 by gcollet          ###   ########.fr       */
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
		s.ret = ft_putchar('%', s.ret);
	else
	{
		s.len = -1;
		return (s);
	}
	return (s);
}
