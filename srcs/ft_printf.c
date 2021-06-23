/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 12:05:56 by gcollet           #+#    #+#             */
/*   Updated: 2021/06/23 16:10:40 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_putchar(char c, int ret)
{
	write (1, &c, 1);
	ret++;
	return (ret);
}

int	ft_putstr(char *s, int ret)
{
	while (*s)
	{
		ret = ft_putchar(*s, ret);
		s++;
	}
	return (ret);
}

char	*convert(unsigned long num, int base, int maj)
{
	static char	val[17];
	static char	buffer[50];
	char		*ptr;

	ft_strlcpy(val, "0123456789abcdef", 17);
	if (maj == 1)
		ft_strlcpy(val, "0123456789ABCDEF", 17);
	ptr = &buffer[49];
	*ptr = '\0';
	*--ptr = val[num % base];
	num /= base;
	while (num != 0)
	{
		*--ptr = val[num % base];
		num /= base;
	}
	return (ptr);
}

int	is_a_conversion_specifier(t_s s)
{
	if (*s.format == 'c' || *s.format == 's' || *s.format == 'p'
		|| *s.format == 'd' || *s.format == 'i' || *s.format == 'u'
		|| *s.format == 'x' || *s.format == 'X' || *s.format == '%')
		return (1);
	return (0);
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
		if (*s.format == '0' && s.minus == 0)
		{
			s.zero = 1;
			s.format++;
		}
		s = ft_check2(s);
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
	return (s);
}

int	ft_print_c(char c, t_s s)
{
	if (s.minus == 1)
		s.ret = ft_putchar(c, s.ret);
	while (s.width > 1)
	{
		s.width--;
		s.ret = ft_putchar(' ', s.ret);
	}
	if (s.minus == 0)
		s.ret = ft_putchar(c, s.ret);
	return (s.ret);
}

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

t_s	ft_print_dori1(t_s s)
{
	if ((s.minus == 1) || ((s.i < 0) && (s.zero == 1)
			&& (s.precision == -1)))
	{
		if (s.i < 0)
		{
			s.i = -s.i;
			s.ret = ft_putchar('-', s.ret);
			s.width--;
		}
	}
	return (s);
}

t_s	ft_print_dori2(t_s s)
{
	if ((s.minus == 0) && (s.precision != 0))
	{
		if (s.i < 0)
			s.width--;
		while ((s.width > s.precision) && (s.width > s.digit))
		{
			if ((s.zero == 1) && (s.precision >= s.width))
				s.ret = ft_putchar('0', s.ret);
			else if ((s.zero == 1) && (s.precision == -1))
				s.ret = ft_putchar('0', s.ret);
			else
				s.ret = ft_putchar(' ', s.ret);
			s.width--;
		}
	}
	if ((s.i < 0 && s.zero == 1) || (s.i < 0 && s.minus == 0))
	{
		s.width--;
		if (s.width <= s.digit)
		{
			s.i = -s.i;
			s.ret = ft_putchar('-', s.ret);
		}
	}
	return (s);
}

t_s	ft_print_dori3_1(t_s s)
{
	if (s.minus == 0)
	{
		if (s.i < 0)
		{
			s.i = -s.i;
			s.ret = ft_putchar('-', s.ret);
			s.width--;
		}
		s.ret = ft_putstr(convert(s.i, 10, 0), s.ret);
	}
	return (s);
}

t_s	ft_print_dori3(t_s s)
{
	if (s.precision == 0)
	{
		if ((s.minus == 1) && (s.i != 0))
			s.ret = ft_putstr(convert(s.i, 10, 0), s.ret);
		while (--s.width + 1 > s.digit)
			s.ret = ft_putchar(' ', s.ret);
		if (s.i == 0)
		{
			while (--s.width + 1 >= 0)
				s.ret = ft_putchar(' ', s.ret);
			s.digit = -1;
			return (s);
		}
		s = ft_print_dori3_1(s);
		s.digit = -1;
		return (s);
	}
	return (s);
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
		s.ret = ft_putstr(convert(s.i, 10, 0), s.ret);
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
		s.ret = ft_putstr(convert(s.i, 10, 0), s.ret);
	}
	return (s);
}

int	ft_print_dori(long i, t_s s)
{
	s.i = i;
	s.digit = ft_digit(s.i);
	s = ft_print_dori1(s);
	s = ft_print_dori2(s);
	s = ft_print_dori3(s);
	if (s.digit == -1)
		return (s.ret);
	s = ft_print_dori4(s);
	s = ft_print_dori5(s);
	return (s.ret);
}

t_s	ft_print_s1(t_s s)
{
	if (s.precision == 0)
		s.len = 0;
	while ((s.width > s.len) || (s.width > s.precision))
	{
		while ((s.width > s.precision) && (s.precision != -1))
		{
			s.ret = ft_putchar(' ', s.ret);
			s.width--;
		}
		if (--s.width + 1 > s.len)
			s.ret = ft_putchar(' ', s.ret);
	}
	if (s.precision == -1)
		s.ret = ft_putstr(s.ptr, s.ret);
	if (s.precision > 0)
	{
		while (s.precision > 0 && s.ptr[0])
		{
			s.ret = ft_putchar(s.ptr[0], s.ret);
			s.ptr++;
			s.precision--;
		}
	}
	return (s);
}

t_s	ft_print_s2(t_s s)
{
	while ((++s.temp) < s.len && (s.precision > 0))
	{
		if ((s.width != 0) && (s.minus != 1))
			s.ret = ft_putchar(' ', s.ret);
	}
	if (s.precision > 0)
	{
		while (s.precision > 0 && s.ptr[0])
		{
			s.ret = ft_putchar(s.ptr[0], s.ret);
			s.ptr++;
			s.precision--;
			s.width--;
		}
	}
	else if (s.precision != 0)
	{
		s.ret = ft_putstr(s.ptr, s.ret);
		s.width -= s.len;
	}
	while (--s.width + 1 > 0)
		s.ret = ft_putchar(' ', s.ret);
	return (s);
}

int	ft_print_s(char *ptr, t_s s)
{
	s.temp = s.precision;
	if (ptr == NULL)
		ptr = "(null)";
	s.ptr = ptr;
	s.len = ft_strlen(ptr);
	if ((s.width > 0) && (s.minus == 0))
		s = ft_print_s1(s);
	else
		s = ft_print_s2(s);
	return (s.ret);
}

int	ft_p(char *ptr, t_s s)
{
	int	len;

	len = (ft_strlen(ptr) + 2);
	if ((s.width > 0) && (s.minus == 0))
	{
		while (--s.width + 1 > len)
			s.ret = ft_putchar(' ', s.ret);
		s.ret = ft_putstr("0x", s.ret);
		s.ret = ft_putstr(ptr, s.ret);
	}
	else
	{
		s.ret = ft_putstr("0x", s.ret);
		s.ret = ft_putstr(ptr, s.ret);
		s.width -= len;
		while (--s.width + 1 > 0)
			s.ret = ft_putchar(' ', s.ret);
	}
	return (s.ret);
}

t_s	ft_uint1(t_s s)
{
	if ((s.minus == 0) && (s.precision != -1))
	{
		while ((s.width > s.precision) && (s.width > s.len))
		{
			s.width--;
			s.ret = ft_putchar(' ', s.ret);
		}
	}
	if (s.precision == 0)
	{
		if (*s.ptr != '0')
			s.ret = ft_putstr(s.ptr, s.ret);
		else if ((s.precision == 0 && *s.ptr != '0') || (s.width > 0))
			s.ret = ft_putchar(' ', s.ret);
		s.width -= s.len;
		while (--s.width + 1 > 0)
			s.ret = ft_putchar(' ', s.ret);
		s.len = -1;
		return (s);
	}
	return (s);
}

int	ft_uint(char *ptr, t_s s)
{
	s.ptr = ptr;
	s.len = ft_strlen(ptr);
	s = ft_uint1(s);
	if (s.len == -1)
		return (s.ret);
	while (s.precision > s.len)
	{
		s.precision--;
		s.width--;
		s.ret = ft_putchar('0', s.ret);
	}
	if ((s.minus == 1) || (s.precision != -1))
		s.ret = ft_putstr(s.ptr, s.ret);
	while (s.width > s.len)
	{
		s.width--;
		if ((s.minus == 0) && (s.precision == -1) && (s.zero == 1))
			s.ret = ft_putchar('0', s.ret);
		else
			s.ret = ft_putchar(' ', s.ret);
	}
	if ((s.minus == 0) && (s.precision == -1))
		s.ret = ft_putstr(s.ptr, s.ret);
	return (s.ret);
}

t_s	ft_format(va_list ap, t_s s)
{
	if (*s.format == 'c')
		s.ret = ft_print_c(va_arg(ap, int), s);
	else if (*s.format == 'd' || *s.format == 'i')
		s.ret = ft_print_dori(va_arg(ap, int), s);
	else if (*s.format == 's')
		s.ret = ft_print_s(va_arg(ap, char *), s);
	else if (*s.format == 'p')
		s.ret = ft_p(convert(va_arg(ap, unsigned long), 16, 0), s);
	else if (*s.format == 'u')
		s.ret = ft_uint(convert(va_arg(ap, unsigned int), 10, 0), s);
	else if (*s.format == 'x')
		s.ret = ft_uint(convert(va_arg(ap, unsigned int), 16, 0), s);
	else if (*s.format == 'X')
		s.ret = ft_uint(convert(va_arg(ap, unsigned int), 16, 1), s);
	else if (*s.format == '%')
		s.ret = ft_putchar('%', s.ret);
	else
	{
		s.len = -1;
		return (s);
	}
	return (s);
}

t_s	ft_astrerisk(va_list ap, t_s s)
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

t_s	ft_print_text(t_s s)
{
	while (*s.format != '%' && *s.format != '\0')
	{
		s.ret = ft_putchar(*s.format, s.ret);
		s.format++;
	}
	return (s);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	t_s		s;

	s.ret = 0;
	s.format = format;
	va_start(ap, format);
	while (*s.format != '\0')
	{
		s = ft_print_text(s);
		if (*s.format == '\0')
			break ;
		s.format++;
		s = ft_initialize_flag(s);
		s = ft_check(s);
		s = ft_astrerisk(ap, s);
		s = ft_format(ap, s);
		if (s.len == -1)
			return (s.ret);
		s.format++;
	}
	va_end(ap);
	return (s.ret);
}
