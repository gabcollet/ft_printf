/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_e1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 13:07:06 by gcollet           #+#    #+#             */
/*   Updated: 2021/07/05 16:12:03 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

t_s	ft_print_e4(t_s s)
{
	s = ft_fnegative(s);
	if ((s.minus == 1) || (s.precision != -1))
	{
		s = ft_ftoa(s.d, s);
		free (s.ptr);
	}
	return (s);
}

t_s	ft_print_e5(t_s s)
{
	int temp;
	
	if ((s.fdigit < 6) && (s.precision == -1))
	{
		s.temp = s.fdigit;
		s.fdigit = 6;
	}
	temp = s.digit;
	if (s.e == 1)
		s.digit++;
	while (s.width > (s.digit + s.fdigit + 4))
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
	s.digit = temp;
	if ((s.minus == 0) && (s.precision == -1))
	{
		s = ft_fnegative(s);
		s = ft_ftoa(s.d, s);
		free (s.ptr);
	}
	s.fdigit = s.temp;
	return (s);
}