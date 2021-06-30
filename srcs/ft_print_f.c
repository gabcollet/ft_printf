/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_f.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 10:47:11 by gcollet           #+#    #+#             */
/*   Updated: 2021/06/30 16:31:44 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

t_s	ft_print_f1(t_s s)
{
	if ((s.minus == 1) || ((s.d < 0) && (s.zero == 1)
			/* && (s.precision == -1) */))
		s = ft_fnegative(s);
	if ((s.minus == 0) && (s.precision > 0))
	{
		if ((s.d < 0) || (s.plus == 1) || (s.space == 1))
			s.width -= s.digit + 2;
		else
			s.width -= s.digit + 1;
		while (s.width > s.precision)
		{
			if ((s.zero == 1) && (s.precision >= s.width))
				s.ret = ft_putchar('0', s.ret);
			if ((s.plus != 1) && (s.space != 1))
			{
				if (s.zero == 1) /* && (s.precision == -1) */
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

t_s	ft_print_f2(t_s s)
{
	if ((s.d < 0 && s.zero == 1) || (s.d < 0 && s.minus == 0))
	{
		/* s.width--; */
		if (s.width <= s.digit)
			s = ft_fnegative(s);
	}
	return (s);
}

t_s	ft_print_f3(t_s s)
{
	if (s.precision == 0)
	{
		s.fdigit = 0;
		if (s.minus == 1) /* && (s.d != 0)) */
		{
			s.ptr = ft_ftoa(s.d, s.fdigit, s);
			s.ret = ft_putstr(s.ptr, s.ret);
			free (s.ptr);
		}
		while (--s.width + 1 > s.digit)
		{
			if (s.zero == 1)
				s.ret = ft_putchar('0', s.ret);
			else
				s.ret = ft_putchar(' ', s.ret);
		}
		/* if (s.d == 0)
		{
			while (--s.width + 1 >= 0)
				s.ret = ft_putchar(' ', s.ret);
			s = ft_negative(s);
			s.digit = -1;
			return (s);
		} */
		if (s.minus == 0)
		{
			s = ft_fnegative(s);
			s.ptr = ft_ftoa(s.d, s.fdigit, s);
			s.ret = ft_putstr(s.ptr, s.ret);
			free (s.ptr);
		}
		s.digit = -1;
		return (s);
	}
	return (s);
}

int	ft_print_f(double d, t_s s)
{
	s.d = d;
	/* s.width -= 7; */
	s = ft_digit_f(s);
	s = ft_print_f1(s);
	s = ft_print_f2(s);
	s = ft_print_f3(s);
	if (s.digit == -1)
		return (s.ret);
	s = ft_print_f4(s);
	s = ft_print_f5(s);
	return (s.ret);
}
