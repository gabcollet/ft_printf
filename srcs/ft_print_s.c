/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_s.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 11:57:36 by gcollet           #+#    #+#             */
/*   Updated: 2021/07/01 14:13:02 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

t_s	ft_print_s1(t_s s)
{
	if (s.precision == 0)
		s.len = 0;
	while ((s.width > s.len) || (s.width > s.precision))
	{
		while ((s.width > s.precision) && (s.precision != -1))
		{
			s.ret = ft_putchar(' ', s.ret);
			s.width--;
		}
		if (--s.width + 1 > s.len)
			s.ret = ft_putchar(' ', s.ret);
	}
	if (s.precision == -1)
		s.ret = ft_putstr(s.ptr, s.ret);
	if (s.precision > 0)
	{
		while (s.precision > 0 && s.ptr[0])
		{
			s.ret = ft_putchar(s.ptr[0], s.ret);
			s.ptr++;
			s.precision--;
		}
	}
	return (s);
}

t_s	ft_print_s2(t_s s)
{
	while ((++s.temp) < s.len && (s.precision > 0))
	{
		if ((s.width != 0) && (s.minus != 1))
			s.ret = ft_putchar(' ', s.ret);
	}
	if (s.precision > 0)
	{
		while (s.precision > 0 && s.ptr[0])
		{
			s.ret = ft_putchar(s.ptr[0], s.ret);
			s.ptr++;
			s.precision--;
			s.width--;
		}
	}
	else if ((s.precision != 0) || (s.plus == -1))
	{
		s.ret = ft_putstr(s.ptr, s.ret);
		s.width -= s.len;
	}
	while (--s.width + 1 > 0)
		s.ret = ft_putchar(' ', s.ret);
	return (s);
}

int	ft_print_s(char *ptr, t_s s)
{
	s.temp = s.precision;
	if (ptr == NULL)
		ptr = "(null)";
	s.ptr = ptr;
	s.len = ft_strlen(ptr);
	if ((s.width > 0) && (s.minus == 0))
		s = ft_print_s1(s);
	else
		s = ft_print_s2(s);
	return (s.ret);
}
