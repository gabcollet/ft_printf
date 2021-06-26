/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_dori1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 11:02:11 by gcollet           #+#    #+#             */
/*   Updated: 2021/06/26 18:54:06 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_digit(int i)
{
	int	temp;
	int	digit;

	temp = i;
	digit = 0;
	if (i == 0)
		digit++;
	while (temp != 0)
	{
		temp = temp / 10;
		digit++;
	}
	return (digit);
}

t_s	ft_negative(t_s s)
{	
	if ((s.i < 0) && (s.len == 0))
	{
		s.i = -s.i;
		if (s.i == LONG_MIN)
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

t_s	ft_print_dori4(t_s s)
{
	s = ft_negative(s);
	while (s.precision > s.digit)
	{
		s.precision--;
		s.width--;
		s.ret = ft_putchar('0', s.ret);
	}
	if ((s.minus == 1) || (s.precision != -1))
		s.ret = ft_putstr(ft_convert(s.i, 10, 0), s.ret);
	return (s);
}

t_s	ft_print_dori5(t_s s)
{
	while (s.width > s.digit)
	{
		s.width--;
		if ((s.minus == 0) && (s.precision == -1) && (s.zero == 1))
		{
			s = ft_negative(s);
			s.ret = ft_putchar('0', s.ret);
		}
		else
			s.ret = ft_putchar(' ', s.ret);
	}
	if ((s.minus == 0) && (s.precision == -1))
	{
		s = ft_negative(s);
		s.ret = ft_putstr(ft_convert(s.i, 10, 0), s.ret);
	}
	return (s);
}
