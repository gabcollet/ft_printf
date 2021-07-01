/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 12:20:36 by gcollet           #+#    #+#             */
/*   Updated: 2021/07/01 18:13:41 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	reverse(char *str, int len)
{
	int	i;
	int	j;
	int	temp;

	i = 0;
	j = len - 1;
	while (i < j)
	{
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		i++;
		j--;
	}
}

int	ft_intToStr(long x, char str[], int d)
{
	int	i;

	i = 0;
	if (x == 0)
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
	while (i < d)
		str[i++] = '0';
	reverse(str, i);
	str[i] = '\0';
	return (i);
}

int	ft_alt_rev_intToStr(long x, char str[], int d)
{
	int	i;

	i = 0;
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
	reverse(str, i);
	while (i < d)
		str[i++] = '0';
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

t_s	ft_ftoa(double n, t_s s)
{
	long	ipart;
	double	fpart;
	int		i;
	int		temp;

	temp = s.fdigit;
	i = 0;
	s.ptr = (char *)malloc(sizeof(char) * (3 + DBL_MANT_DIG - DBL_MIN_EXP));
	if (s.precision == 0)
	{
		n = (n + .5) * 10;
		n /= 10;
		ipart = (long)n;
		if (((ipart / 2) * 2 != ipart) && (s.fdigit < 2))
			ipart -= 1;
		s.fdigit = 0;
	}
	else
		ipart = (long)n;
	fpart = n - ipart;
	if ((s.precision == -1) || ((s.fdigit < 6) && (s.precision != 0)))
		s.fdigit = 6;
	i = ft_intToStr(ipart, s.ptr, 0);
	if (s.fdigit != 0)
	{
		s.ptr[i] = '.';
		if (fpart == ULLONG_MAX)
			fpart = 0;
		if (s.precision != -1)
			s.fdigit = s.precision;
		if ((fpart != 0) && (s.precision != -1))
			fpart = ft_round_up(s.fdigit, n);
		else
		{
			if (temp > 6)
				temp = 6;
			while (temp != 0)
			{
				fpart *= 10;
				temp--;
				if ((int)fpart == 0)
				{
					i += ft_intToStr(0, s.ptr + i + 1, 0);
					s.fdigit--;
				}
			}
			ft_alt_rev_intToStr((long)fpart, s.ptr + i + 1, s.fdigit);
			return (s);
		}
		if (s.fdigit != 0)
			ft_intToStr((long)fpart, s.ptr + i + 1, s.fdigit);
	}
	return (s);
}
