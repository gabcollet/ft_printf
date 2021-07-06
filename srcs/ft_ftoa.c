/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 12:20:36 by gcollet           #+#    #+#             */
/*   Updated: 2021/07/06 14:28:04 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_intToStr(long x, char str[], int d, int a)
{
	int	i;

	i = 0;
	if (x == 0 && a == 0)
		str[i++] = '0';
	if (x == LLONG_MIN)
	{
		x = x / 10;
		x = -x;
		str[i++] = '8';
	}
	while (x)
	{
		str[i++] = (x % 10) + '0';
		x = x / 10;
	}
	if (a == 1)
		reverse(str, i);
	while (i < d)
		str[i++] = '0';
	if (a == 0)
		reverse(str, i);
	str[i] = '\0';
	return (i);
}

double	ft_round_up(int fdigit, double n)
{
	unsigned long long	round;
	long double			ll;

	round = 10;
	while (fdigit - 1 > 0)
	{
		round *= 10;
		fdigit--;
	}
	ll = (long long)(n * round + .5);
	return (ll);
}

t_s	ft_ftoa2(t_s s)
{
	if (s.precision == 0)
	{
		s.d = (s.d + .5) * 10;
		s.d /= 10;
		s.ipart = (long)s.d;
		if (((s.ipart / 2) * 2 != s.ipart) && (s.fdigit < 2) && (s.ipart != 1))
			s.ipart -= 1;
		s.fdigit = 0;
	}
	else
		s.ipart = (long)s.d;
	s.fpart = s.d - s.ipart;
	if ((s.precision == -1) || ((s.fdigit < 6) && (s.precision != 0)))
		s.fdigit = 6;
	s.y = ft_intToStr(s.ipart, s.ptr, 0, 0);
	if (s.sharp == 1)
	{
		s.ptr[s.y] = '.';
		s.width--;
	}
	return (s);
}

t_s	ft_ftoa3(t_s s, int temp)
{
	if (temp > 6)
		temp = 6;
	while (temp != 0)
	{
		s.fpart *= 10;
		temp--;
		if ((int)s.fpart == 0)
		{
			s.y += ft_intToStr(0, s.ptr + s.y + 1, 0, 0);
			s.fdigit--;
		}
	}
	ft_intToStr((long)s.fpart, s.ptr + s.y + 1, s.fdigit, 1);
	s.ret = ft_putstr(s.ptr, s.ret);
	return (s);
}

t_s	ft_ftoa(t_s s)
{
	int		temp;

	temp = s.fdigit;
	s.y = 0;
	s.ptr = (char *)malloc(sizeof(char) * (3 + DBL_MANT_DIG - DBL_MIN_EXP));
	s = ft_ftoa2(s);
	if (s.fdigit != 0)
	{
		s.ptr[s.y] = '.';
		if (s.fpart == ULLONG_MAX)
			s.fpart = 0;
		if (s.precision != -1)
			s.fdigit = s.precision;
		if ((s.fpart != 0) && (s.precision != -1))
			s.fpart = ft_round_up(s.fdigit, s.d);
		else
		{
			s = ft_ftoa3(s, temp);
			return (s);
		}
		if (s.fdigit != 0)
			ft_intToStr((long)s.fpart, s.ptr + s.y + 1, s.fdigit, 0);
	}
	s.ret = ft_putstr(s.ptr, s.ret);
	return (s);
}
