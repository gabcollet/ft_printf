/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_flags.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 11:04:10 by gcollet           #+#    #+#             */
/*   Updated: 2021/07/06 13:42:23 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	is_a_conversion_specifier(t_s s)
{
	if (*s.format == 'c' || *s.format == 's' || *s.format == 'p'
		|| *s.format == 'd' || *s.format == 'i' || *s.format == 'u'
		|| *s.format == 'x' || *s.format == 'X' || *s.format == '%'
		|| *s.format == 'n' || *s.format == 'f' || *s.format == 'e')
		return (1);
	return (0);
}

t_s	ft_asterisk(va_list ap, t_s s)
{
	if (s.w_asterisk == 1)
	{
		s.width = va_arg(ap, int);
		if (s.width < 0)
		{
			s.width = -s.width;
			s.minus = 1;
		}
	}
	if (s.p_asterisk == 1)
	{
		s.precision = va_arg(ap, int);
		if (s.precision < 0)
			s.precision = -1;
	}
	return (s);
}

t_s	ft_check2(t_s s)
{
	if (*s.format == '*')
	{
		s.w_asterisk = 1;
		s.format++;
	}
	if (*s.format >= '0' && *s.format <= '9')
	{
		s.width = ft_atoi(s.format);
		while (*s.format >= '0' && *s.format <= '9')
			s.format++;
	}
	if (*s.format == '.')
	{
		s.format++;
		if (*s.format == '*')
		{
			s.p_asterisk = 1;
			s.format++;
		}
		s.precision = ft_atoi(s.format);
		while (!(is_a_conversion_specifier(s)))
			s.format++;
	}
	return (s);
}

t_s	ft_check(t_s s)
{	
	while (!(is_a_conversion_specifier(s)))
	{
		if (*s.format == '-')
		{
			s.minus = 1;
			if (s.zero == 1)
				s.zero = 0;
			s.format++;
		}
		s = ft_check_bonus(s);
		if (*s.format == '0' && s.minus == 0)
		{
			s.zero = 1;
			s.format++;
		}
		s = ft_check2(s);
		s = ft_check_length(s);
	}
	return (s);
}

t_s	ft_initialize_flag(t_s s)
{
	s.minus = 0;
	s.precision = -1;
	s.zero = 0;
	s.width = 0;
	s.w_asterisk = 0;
	s.p_asterisk = 0;
	s.plus = 0;
	s.space = 0;
	s.len = 0;
	s.temp = 0;
	s.digit = 0;
	s.fdigit = 0;
	s.l = 0;
	s.ll = 0;
	s.h = 0;
	s.hh = 0;
	s.sharp = 0;
	return (s);
}
