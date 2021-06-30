/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_flags_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 11:53:15 by gcollet           #+#    #+#             */
/*   Updated: 2021/06/30 10:13:34 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

t_s	ft_length_format(va_list ap, t_s s)
{
	if (s.l == 1)
		s = ft_format_l(ap, s);
	else if (s.ll == 1)
		s = ft_format_ll(ap, s);
	else if (s.h == 1)
		s = ft_format_h(ap, s);
	else if (s.hh == 1)
		s = ft_format_hh(ap, s);
	else
		s = ft_format(ap, s);
	return (s);
}

t_s	ft_check_bonus(t_s s)
{
	if (*s.format == '+')
	{
		s.plus = 1;
		s.format++;
	}
	if (*s.format == ' ')
	{
		s.space = 1;
		s.format++;
	}
	if (*s.format == '#')
	{
		s.sharp = 1;
		s.format++;
	}
	return (s);
}

t_s	ft_check_length(t_s s)
{
	if (*s.format == 'l')
	{
		s.format++;
		if (*s.format == 'l')
		{
			s.ll = 1;
			s.format++;
		}
		else
			s.l = 1;
	}
	if (*s.format == 'h')
	{
		s.format++;
		if (*s.format == 'h')
		{
			s.hh = 1;
			s.format++;
		}
		else
			s.h = 1;
	}
	return (s);
}
