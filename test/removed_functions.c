/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 13:34:05 by gcollet           #+#    #+#             */
/*   Updated: 2021/07/06 13:38:04 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long ft_rev(unsigned long long fpart, int precision)
{
	int		remainder;
	long		temp;

	if (precision == -1)
		precision = 6;
	remainder = 0;
	temp = 0;
	while ((fpart != 0) && (precision != 0))
	{
		remainder = (long long)fpart % 10;
		temp = temp * 10 + remainder;
		fpart /= 10;
		precision--;
	}
	return (temp);
}

t_s ft_print_ex(t_s s)
{
	char	*c;
	
	s.ret = ft_putchar('e', s.ret);
	if (s.temp >= 0)
		s.ret = ft_putchar('+', s.ret);
	else
		s.ret = ft_putchar('-', s.ret);
	if (s.temp < 10 && s.temp > -10)
		s.ret = ft_putchar('0', s.ret);
    if (s.temp < 0)
        s.temp = -s.temp;
	c = ft_itoa(s.temp);
	s.ret = ft_putstr(c, s.ret);
	free (c);
	return (s);
}

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

t_s	ft_print_e1(t_s s)
{
	int temp;
	
	temp = s.digit;
	s.digit = 1;
	if ((s.minus == 1) || ((s.d < 0) && (s.width < s.fdigit + 5)))
		s = ft_fnegative(s);
		
	if ((s.minus == 0) && (s.precision > 0))
	{
/* 		if ((s.d < 0) || (s.plus == 1) || (s.space == 1))
			s.width -= s.digit + 2;
		else
			s.width -= s.digit + 1; */
		if (s.d < 0)
			s.width--;
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

t_s	ft_ftoa_e(long double n, t_s s)
{
	unsigned long long	ipart;
	unsigned long long	fpart;
	int		i;
	long long		temp;
	int		a;

	temp = s.fdigit;
	i = 0;
	fpart = 0;
    s.temp = 0;
	s.ptr = (char *)malloc(sizeof(char) * (3 + DBL_MANT_DIG - DBL_MIN_EXP));
	if ((s.precision == 0) && (n <= -1 || n >= 1))
	{
		n = (n + .5) * 10;
		n /= 10;
		ipart = (long)n;
		if (((ipart / 2) * 2 != ipart) && (s.fdigit < 2) && (ipart != 1))
			ipart -= 1;
		s.fdigit = 0;
	}
	else
		ipart = (unsigned long long)n;
    while ((ipart == 0) && (n != 0))
    {
        n *= 10;
        ipart = n;
        s.temp--;
    }
    if (s.digit > 1)
	{
		while (s.digit > 1)
		{
			fpart *= 10;
			fpart += (ipart % 10);
			ipart /= 10;
			s.digit--;
			s.temp++;
			temp--;
		}
		fpart = ft_rev(fpart, s.precision);
	}
	else if (n != 0)
	{
		a = s.precision;
		while (a > 0)
		{
			fpart *= 10;
			n *= 10;
			fpart += ((long long)n % 10);
			a--;
		}
        a = -1;
	}
	if ((s.precision == -1) || ((s.fdigit < 6) && (s.precision != 0)))
		s.fdigit = 6;
	i = ft_intToStr(ipart, s.ptr, 0, 0);
	if (s.sharp == 1)
	{
		s.ptr[i] = '.';
		s.width--;
	}
	if ((s.fdigit != 0) && (!((s.width == -1) && (s.precision == 0))))
	{
		s.ptr[i] = '.';
		if (fpart == ULLONG_MAX)
			fpart = 0;
		if (s.precision != -1)
			s.fdigit = s.precision;
		if ((fpart != 0) && (s.precision != -1))
		{
			if ((s.fdigit > 1) && (a != -1))
				fpart = ft_round_up(s.fdigit - 1, fpart);
		}
		else
		{
			if (temp > 6)
				temp = 6;
			/* n = n - ipart; */
			while (temp != 0)
			{
				fpart *= 10;
				n *= 10;
				fpart += ((long long)n % 10);
				temp--;
				if (((int)fpart == 0) && (s.fdigit != 0))
				{
					i += ft_intToStr(0, s.ptr + i + 1, 0, 0);
					s.fdigit--;
				}
			}
			ft_intToStr((long)fpart, s.ptr + i + 1, s.fdigit, 1);
			s.ret = ft_putstr(s.ptr, s.ret);
			s = ft_print_ex(s);
			return (s);
		}
		if (s.fdigit != 0)
			ft_intToStr((long)fpart, s.ptr + i + 1, s.fdigit, 0);
	}
	s.ret = ft_putstr(s.ptr, s.ret);
	s = ft_print_ex(s);
	return (s);
}