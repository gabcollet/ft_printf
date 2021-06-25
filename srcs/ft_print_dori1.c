/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_dori1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 11:02:11 by gcollet           #+#    #+#             */
/*   Updated: 2021/06/25 12:11:54 by gcollet          ###   ########.fr       */
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

t_s	ft_print_dori4(t_s s)
{
	while (s.precision > s.digit)
	{
		if (s.i < 0)
		{
			s.i = -s.i;
			s.ret = ft_putchar('-', s.ret);
			s.width--;
		}
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
			if (s.i < 0)
			{
				s.i = -s.i;
				s.ret = ft_putchar('-', s.ret);
			}
			s.ret = ft_putchar('0', s.ret);
		}
		else
			s.ret = ft_putchar(' ', s.ret);
	}
	if ((s.minus == 0) && (s.precision == -1))
	{
		if (s.i < 0)
		{
			s.i = -s.i;
			s.ret = ft_putchar('-', s.ret);
		}
		s.ret = ft_putstr(ft_convert(s.i, 10, 0), s.ret);
	}
	return (s);
}
