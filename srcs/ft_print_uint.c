/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_uint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 12:03:18 by gcollet           #+#    #+#             */
/*   Updated: 2021/06/25 12:04:14 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

t_s	ft_print_uint1(t_s s)
{
	if ((s.minus == 0) && (s.precision != -1))
	{
		while ((s.width > s.precision) && (s.width > s.len))
		{
			s.width--;
			s.ret = ft_putchar(' ', s.ret);
		}
	}
	if (s.precision == 0)
	{
		if (*s.ptr != '0')
			s.ret = ft_putstr(s.ptr, s.ret);
		else if ((s.precision == 0 && *s.ptr != '0') || (s.width > 0))
			s.ret = ft_putchar(' ', s.ret);
		s.width -= s.len;
		while (--s.width + 1 > 0)
			s.ret = ft_putchar(' ', s.ret);
		s.len = -1;
		return (s);
	}
	return (s);
}

int	ft_print_uint(char *ptr, t_s s)
{
	s.ptr = ptr;
	s.len = ft_strlen(ptr);
	s = ft_print_uint1(s);
	if (s.len == -1)
		return (s.ret);
	while (s.precision > s.len)
	{
		s.precision--;
		s.width--;
		s.ret = ft_putchar('0', s.ret);
	}
	if ((s.minus == 1) || (s.precision != -1))
		s.ret = ft_putstr(s.ptr, s.ret);
	while (s.width > s.len)
	{
		s.width--;
		if ((s.minus == 0) && (s.precision == -1) && (s.zero == 1))
			s.ret = ft_putchar('0', s.ret);
		else
			s.ret = ft_putchar(' ', s.ret);
	}
	if ((s.minus == 0) && (s.precision == -1))
		s.ret = ft_putstr(s.ptr, s.ret);
	return (s.ret);
}
