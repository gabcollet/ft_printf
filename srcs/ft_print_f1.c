/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_f1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 10:47:41 by gcollet           #+#    #+#             */
/*   Updated: 2021/06/30 16:47:08 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

t_s	ft_digit_f(t_s s)
{
	double	f;
	long long temp;

	s.digit = 0;
	f = s.d;
	temp = s.d;
	while(f != ((int)f))
	{
		s.fdigit++;
		f *= 10;
        if (s.fdigit > 7)
        {
            s.fdigit = 6;
            break ;
        }
	}
	if (s.d == 0)
		s.digit++;
	while (temp != 0)
	{
		temp = temp / 10;
		s.digit++;
	}
	if (s.fdigit < 6)
		s.fdigit = 6;
	return (s);
}

t_s	ft_fnegative(t_s s)
{	
	if ((s.d < 0) && (s.len == 0))
	{
		s.d = -s.d;
		if (s.d == LONG_MIN)
			s.len = 1;
		s.ret = ft_putchar('-', s.ret);
		s.width--;
		s.plus--;
		s.space--;
	}
	else if (s.plus == 1)
	{
		s.ret = ft_putchar('+', s.ret);
		s.plus--;
		s.width--;
	}
	else if (s.space == 1)
	{
		s.ret = ft_putchar(' ', s.ret);
		s.space--;
		s.width--;
	}
	return (s);
}

t_s	ft_print_f4(t_s s)
{
	s = ft_fnegative(s);
/* 	while (s.precision > s.digit)
	{
		s.precision--;
		s.width--;
		s.ret = ft_putchar('0', s.ret);
	} */
	if ((s.minus == 1) || (s.precision != -1))
	{
        s.fdigit = s.precision;
		s.ptr = ft_ftoa(s.d, s.fdigit, s);
		s.ret = ft_putstr(s.ptr, s.ret);
		free (s.ptr);
	}
	return (s);
}

t_s	ft_print_f5(t_s s)
{
	while (s.width > (s.digit + s.fdigit + 1))
	{
		s.width--;
		if ((s.minus == 0) && (s.precision == -1) && (s.zero == 1))
		{
			s = ft_fnegative(s);
			s.ret = ft_putchar('0', s.ret);
		}
		else
			s.ret = ft_putchar(' ', s.ret);
	}
	if ((s.minus == 0) && (s.precision == -1))
	{
		s = ft_fnegative(s);
		s.ptr = ft_ftoa(s.d, s.fdigit, s);
		s.ret = ft_putstr(s.ptr, s.ret);
		free (s.ptr);
	}
	return (s);
}
