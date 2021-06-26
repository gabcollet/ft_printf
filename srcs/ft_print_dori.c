/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_dori.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 10:58:09 by gcollet           #+#    #+#             */
/*   Updated: 2021/06/26 16:07:51 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

t_s	ft_print_dori1(t_s s)
{
	if ((s.minus == 1) || ((s.i < 0) && (s.zero == 1)
			&& (s.precision == -1)))
		s = ft_negative(s);
	if ((s.minus == 0) && (s.precision != 0))
	{
		if ((s.i < 0) || (s.plus == 1) || (s.space == 1))
			s.width--;
		while ((s.width > s.precision) && (s.width > s.digit))
		{
			if ((s.zero == 1) && (s.precision >= s.width))
				s.ret = ft_putchar('0', s.ret);
			if ((s.plus != 1) && (s.space != 1))
			{
				if ((s.zero == 1) && (s.precision == -1))
					s.ret = ft_putchar('0', s.ret);
				else
					s.ret = ft_putchar(' ', s.ret);
			}
			else
				s.ret = ft_putchar(' ', s.ret);
			s.width--;
		}
	}
	return (s);
}

t_s	ft_print_dori2(t_s s)
{
	if ((s.i < 0 && s.zero == 1) || (s.i < 0 && s.minus == 0))
	{
		s.width--;
		if (s.width <= s.digit)
			s = ft_negative(s);
	}
	return (s);
}

t_s	ft_print_dori3(t_s s)
{
	if (s.precision == 0)
	{
		if ((s.minus == 1) && (s.i != 0))
			s.ret = ft_putstr(ft_convert(s.i, 10, 0), s.ret);
		while (--s.width + 1 > s.digit)
			s.ret = ft_putchar(' ', s.ret);
		if (s.i == 0)
		{
			while (--s.width + 1 >= 0)
				s.ret = ft_putchar(' ', s.ret);
			s = ft_negative(s);
			s.digit = -1;
			return (s);
		}
		if (s.minus == 0)
		{
			s = ft_negative(s);
			s.ret = ft_putstr(ft_convert(s.i, 10, 0), s.ret);
		}
		s.digit = -1;
		return (s);
	}
	return (s);
}

int	ft_print_dori(long i, t_s s)
{
	s.i = i;
	s.digit = ft_digit(s.i);
	s = ft_print_dori1(s);
	s = ft_print_dori2(s);
	s = ft_print_dori3(s);
	if (s.digit == -1)
		return (s.ret);
	s = ft_print_dori4(s);
	s = ft_print_dori5(s);
	return (s.ret);
}
