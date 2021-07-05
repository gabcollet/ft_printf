/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_e.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 13:02:11 by gcollet           #+#    #+#             */
/*   Updated: 2021/07/05 17:21:33 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

t_s	ft_print_e1(t_s s)
{
	int temp;
	
	temp = s.digit;
	s.digit = 1;
	if ((s.minus == 1) || (s.d < 0))
		s = ft_fnegative(s);
	if ((s.minus == 0) && (s.precision > 0))
	{
/* 		if ((s.d < 0) || (s.plus == 1) || (s.space == 1))
			s.width -= s.digit + 2;
		else
			s.width -= s.digit + 1; */
		while (s.width > s.precision + s.digit + 5)
		{
			if ((s.zero == 1) && (s.precision >= s.width))
				s.ret = ft_putchar('0', s.ret);
			if ((s.plus != 1) && (s.space != 1))
			{
				if (s.zero == 1)
					s.ret = ft_putchar('0', s.ret);
				else
					s.ret = ft_putchar(' ', s.ret);
			}
			else
				s.ret = ft_putchar(' ', s.ret);
			s.width--;
		}
	}
	s.digit = temp;
	return (s);
}

t_s	ft_print_e3(t_s s)
{
	int temp; 
	
	if (s.precision == 0)
	{
		temp = s.digit;
		s.digit += 4;
		if (s.minus == 1)
		{
			s.digit = temp; 
			s = ft_ftoa(s.d, s);
			free (s.ptr);
			s.digit += 4;
		}
		while (--s.width + 1 > s.digit)
		{
			if (s.zero == 1)
				s.ret = ft_putchar('0', s.ret);
			else
				s.ret = ft_putchar(' ', s.ret);
		}
		if (s.minus == 0)
		{
			s.digit = temp;
			s = ft_fnegative(s);
			s = ft_ftoa(s.d, s);
			free (s.ptr);
		}
		s.digit = -1;
	}
	return (s);
}

int	ft_print_e(double d, t_s s)
{
	s.d = d;
	if (d != d)
	{
		s.plus = -1;
		s.ret = ft_print_s("nan", s);
		return (s.ret);
	}
	if (d > LONG_MAX)
	{
		s.plus = -1;
		s.ret = ft_print_s("inf", s);
		return (s.ret);
	}
	if (d < LONG_MIN)
	{
		s.plus = -1;
		s.ret = ft_print_s("-inf", s);
		return (s.ret);
	}
	s = ft_digit_f(s);
	s = ft_print_e1(s);
	s = ft_print_e3(s);
	if (s.digit == -1)
		return (s.ret);
	s = ft_print_e4(s);
	s = ft_print_e5(s);
	return (s.ret);
}
