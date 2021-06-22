/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 12:05:56 by gcollet           #+#    #+#             */
/*   Updated: 2021/06/22 16:05:52 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c, int ret)
{
	write (1, &c, 1);
	ret++;
	return(ret);
}

int	ft_putstr(char *s, int ret)
{
	while (*s)
	{
		ret = ft_putchar(*s, ret);
		s++;
	}
	return(ret);
}

char *ft_convert(unsigned long num, int base, int maj)
{
	static char	val[17];
	static char buffer[50];
	char *ptr;
	
	ft_strlcpy(val, "0123456789abcdef", 17);
	if (maj == 1)
		ft_strlcpy(val, "0123456789ABCDEF", 17);
	ptr = &buffer[49];
	*ptr = '\0';

	*--ptr = val[num % base];
	num /= base;
	while(num != 0)
	{
		*--ptr = val[num % base];
		num /= base;
	}
	return(ptr);
}

int is_a_conversion_specifier(const char *format)
{
	if (*format == 'c' || *format == 's' || *format == 'p' || 
		*format == 'd' || *format == 'i' || *format == 'u' || 
		*format == 'x' || *format == 'X' || *format == '%')
		return (1);
	return(0);
}

t_flags	ft_check(const char *format, t_flags flags)
{	
	while (!(is_a_conversion_specifier(format)))
	{
		if (*format == '-')
		{
			flags.minus = 1;
			if (flags.zero == 1)
				flags.zero = 0;
			format++;
		}
		if (*format == '0' && flags.minus == 0)
		{
			flags.zero = 1;
			format++;
		}
		if (*format == '*')
		{
			flags.w_asterisk = 1;
			format++;
		}
		if (*format >= '0' && *format <= '9')
		{
			flags.width = ft_atoi(format);
			while (*format >= '0' && *format <= '9')
				format++;
		}
		if (*format == '.')
		{
			format++;
			if (*format == '*')
			{
				flags.p_asterisk = 1;
				format++;
			}
			flags.precision = ft_atoi(format);
			while (!(is_a_conversion_specifier(format)))
				format++;
		}
	}
	format++;
	return(flags);
}

t_flags	ft_initialize_flag(t_flags flags)
{
	flags.minus = 0;
	flags.precision = -1;
	flags.zero = 0;
	flags.width = 0;
	flags.w_asterisk = 0;
	flags.p_asterisk = 0;
	return(flags);
}

int ft_print_c(char c, int ret, t_flags flags)
{
	if (flags.minus == 1)
		ret = ft_putchar(c, ret);
	while (flags.width > 1)
	{
		flags.width--;
		ret = ft_putchar(' ', ret);
	}
	if (flags.minus == 0)
		ret = ft_putchar(c, ret);
	return(ret);
}

int ft_digit(int digit, int i)
{
	int temp;
	
	temp = i;
	digit = 0;
	if (i == 0)
		digit++;
	while(temp != 0)
	{
		temp = temp/10;
		digit++;
	}
	return (digit);
}

int ft_print_dori(long i, int ret, t_flags flags)
{
	int digit;

	digit = 0;
	digit = ft_digit(digit, i);
	if ((flags.minus == 1) || ((i < 0) && (flags.zero == 1) && (flags.precision == -1)))
	{
		if (i < 0)
		{
			i = -i;
			ret = ft_putchar('-', ret);
			flags.width--;
		}
	}
	if ((flags.minus == 0) && (flags.precision != 0)) 
	{
		if (i < 0)
			flags.width--;
		while ((flags.width > flags.precision) && (flags.width > digit))
		{
			if ((flags.zero == 1) && (flags.precision >= flags.width))
				ret = ft_putchar('0', ret);
			else if ((flags.zero == 1) && (flags.precision == -1))
				ret = ft_putchar('0', ret);
			else
				ret = ft_putchar(' ', ret);
			flags.width--;
		}
	}
	if ((i < 0 && flags.zero == 1) || (i < 0 && flags.minus == 0))
	{
		flags.width--;
		if (flags.width <= digit)
		{
			i = -i;
			ret = ft_putchar('-', ret);
		}
	}
	if (flags.precision == 0)
	{
		if ((flags.minus == 1) && (i != 0))
			ret = ft_putstr(ft_convert(i, 10, 0), ret);
		while (--flags.width + 1 > digit)
			ret = ft_putchar(' ', ret);
		if (i == 0)
		{
			while (--flags.width + 1 >= 0)
				ret = ft_putchar(' ', ret);
			return (ret);	
		}
		if (flags.minus == 0)
		{
			if (i < 0)
			{
				i = -i;
				ret = ft_putchar('-', ret);
				flags.width--;
			}
			ret = ft_putstr(ft_convert(i, 10, 0), ret);
		}
		return (ret);
	}
	while (flags.precision > digit)
	{
		if (i < 0)
		{
			i = -i;
			ret = ft_putchar('-', ret);
			flags.width--;
		}
		flags.precision--;
		flags.width--;
		ret = ft_putchar('0', ret);
	}
	if ((flags.minus == 1) || (flags.precision != -1))
		ret = ft_putstr(ft_convert(i, 10, 0), ret);
	while (flags.width > digit)
	{
		flags.width--;
		if ((flags.minus == 0) && (flags.precision == -1) && (flags.zero == 1))
		{
			if (i < 0)
			{
				i = -i;
				ret = ft_putchar('-', ret);	
			}
			ret = ft_putchar('0', ret);
		}
		else
			ret = ft_putchar(' ', ret);
	}
	if ((flags.minus == 0) && (flags.precision == -1))
	{
		if (i < 0)
		{
			i = -i;
			ret = ft_putchar('-', ret);	
		}
		ret = ft_putstr(ft_convert(i, 10, 0), ret);
	}
	return(ret);
}

int ft_print_s(char *ptr, int ret, t_flags flags)
{
	int len;
	int temp;

	temp = flags.precision;
	if (ptr == NULL)
		ptr = "(null)";
	len = ft_strlen(ptr);
	if ((flags.width > 0) && (flags.minus == 0))
	{
		if (flags.precision == 0)
			len = 0;
		while ((flags.width > len) || (flags.width > flags.precision))
		{
			while ((flags.width > flags.precision) && (flags.precision != -1))
			{
				ret = ft_putchar(' ', ret);
				flags.width--;
			}
			if (--flags.width + 1 > len)
				ret = ft_putchar(' ', ret);
		}
		if (flags.precision == -1)
			ret = ft_putstr(ptr, ret);
		if (flags.precision > 0)
		{
			while (flags.precision > 0 && ptr[0])
			{
				ret = ft_putchar(ptr[0], ret);
				ptr++;
				flags.precision--;
			}
		}		
	}
	else
	{
		while ((++temp) < len && (flags.precision > 0))
		{
			if ((flags.width != 0) && (flags.minus != 1))
				ret = ft_putchar(' ', ret);
		}
		if (flags.precision > 0)
		{
			while (flags.precision > 0 && ptr[0])
			{
				ret = ft_putchar(ptr[0], ret);
				ptr++;
				flags.precision--;
				flags.width--;
			}
		}
		else if (flags.precision != 0)
		{
			ret = ft_putstr(ptr, ret);
			flags.width -= len;
		}
		while (--flags.width + 1 > 0)
			ret = ft_putchar(' ', ret);
	}
	return (ret);
}

int ft_print_p(char *ptr, int ret, t_flags flags)
{
	int len;

	len = (ft_strlen(ptr) + 2);
	if ((flags.width > 0) && (flags.minus == 0))
	{
		while (--flags.width + 1 > len)
			ret = ft_putchar(' ', ret);
		ret = ft_putstr("0x", ret);
		ret = ft_putstr(ptr, ret);
	}
	else
	{
		ret = ft_putstr("0x", ret);
		ret = ft_putstr(ptr, ret);
		flags.width -= len;
		while (--flags.width + 1 > 0)
			ret = ft_putchar(' ', ret);
	}
	return (ret);
}

int ft_print_u(char *ptr, int ret, t_flags flags)
{
	int len;

	len = (ft_strlen(ptr));
	if ((flags.minus == 0) && (flags.precision != -1)) 
	{
		while ((flags.width > flags.precision) && (flags.width > len))
		{
			flags.width--;
			ret = ft_putchar(' ', ret);
		}
	}
	if (flags.precision == 0)
	{
		if (*ptr != '0')
			ret = ft_putstr(ptr, ret);
		else if ((flags.precision == 0 && *ptr != '0') || (flags.width > 0))
			ret = ft_putchar(' ', ret);
		flags.width -= len;
		while (--flags.width + 1 > 0)
			ret = ft_putchar(' ', ret);
		return (ret);
	}
	while (flags.precision > len)
	{
		flags.precision--;
		flags.width--;
		ret = ft_putchar('0', ret);
	}
	if ((flags.minus == 1) || (flags.precision != -1))
			ret = ft_putstr(ptr, ret);
	while (flags.width > len)
	{
		flags.width--;
		if ((flags.minus == 0) && (flags.precision == -1) && (flags.zero == 1))
			ret = ft_putchar('0', ret);
		else
			ret = ft_putchar(' ', ret);
	}
	if ((flags.minus == 0) && (flags.precision == -1))
		ret = ft_putstr(ptr, ret);
	return(ret);
}

int ft_print_x(char *ptr, int ret, t_flags flags)
{
	int len;

	len = (ft_strlen(ptr));
	if ((flags.minus == 0) && (flags.precision != -1)) 
	{
		while ((flags.width > flags.precision) && (flags.width > len))
		{
			flags.width--;
			ret = ft_putchar(' ', ret);
		}
	}
	if (flags.precision == 0)
	{
		if (*ptr != '0')
			ret = ft_putstr(ptr, ret);
		else if ((flags.precision == 0 && *ptr != '0') || (flags.width > 0))
			ret = ft_putchar(' ', ret);
		flags.width -= len;
		while (--flags.width + 1 > 0)
			ret = ft_putchar(' ', ret);
		return (ret);
	}
	while (flags.precision > len)
	{
		flags.precision--;
		flags.width--;
		ret = ft_putchar('0', ret);
	}
	if ((flags.minus == 1) || (flags.precision != -1))
			ret = ft_putstr(ptr, ret);
	while (flags.width > len)
	{
		flags.width--;
		if ((flags.minus == 0) && (flags.precision == -1) && (flags.zero == 1))
			ret = ft_putchar('0', ret);
		else
			ret = ft_putchar(' ', ret);
	}
	if ((flags.minus == 0) && (flags.precision == -1))
		ret = ft_putstr(ptr, ret);
	return(ret);
}

int ft_printf(const char *format, ...)
{
	t_flags flags;
	int ret;

	ret = 0;
	va_list ap;
	va_start(ap, format);
	while (*format != '\0')
	{
		while(*format != '%' && *format != '\0')
		{
			ret = ft_putchar(*format, ret);
			format++;
		}
		if (*format == '\0')
			break;
		format++;
		flags = ft_initialize_flag(flags);
		flags = ft_check(format, flags);
		if (flags.w_asterisk == 1)
		{
			flags.width = va_arg(ap, int);
				if (flags.width < 0)
				{
					flags.width = -flags.width;
					flags.minus = 1;
				}
		}
		if (flags.p_asterisk == 1)
		{
			flags.precision = va_arg(ap, int);
				if (flags.precision < 0)
					flags.precision = -1;
		}
		while (!(is_a_conversion_specifier(format)))
			format++;
		if(*format == 'c')
			ret = ft_print_c(va_arg(ap, int), ret, flags);
		else if(*format == 'd' || *format == 'i')
			ret = ft_print_dori(va_arg(ap, int), ret, flags);
		else if(*format == 's')
			ret = ft_print_s(va_arg(ap, char *), ret, flags);
		else if(*format == 'p')
			ret = ft_print_p(ft_convert(va_arg(ap, unsigned long), 16, 0), ret, flags);
		else if(*format == 'u')
			ret = ft_print_u(ft_convert(va_arg(ap, unsigned int), 10, 0), ret, flags);
		else if(*format == 'x')
			ret = ft_print_x(ft_convert(va_arg(ap, unsigned int), 16, 0), ret, flags);
		else if(*format == 'X')
			ret = ft_print_x(ft_convert(va_arg(ap, unsigned int), 16, 1), ret, flags);
		else if(*format == '%')
			ret = ft_putchar('%', ret);
		else
			return(ret);
		format++;
	}
	va_end(ap);
	return(ret);
}

/* int main()
{
	int ret = 0;
	int retp = 0;
	
	ret = ft_printf("%-8.12s, %3s, %8s, %---2s, %.*s, %.0s, %.1s, %.2s, %.4s, %.8s", NULL, NULL, NULL, NULL, -2, NULL, NULL, NULL, NULL, NULL, NULL);
	printf("\n============================================================\n");
	retp = printf("%-8.12s, %3s, %8s, %---2s, %.*s, %.0s, %.1s, %.2s, %.4s, %.8s", NULL, NULL, NULL, NULL, -2, NULL, NULL, NULL, NULL, NULL, NULL);
	printf("\n#char imprimé ft_printf: %d\n", ret);
	printf("#char imprimé printf: %d\n", retp);
	return 0;
} */

/* int main()
{
	int		a = -4;
	int		b = 0;
	char	c = 'a';
	int		d = 2147483647;
	int		e = -2147483648;
	int		f = 42;
	int		g = 25;
	int		h = 4200;
	int		i = 8;
	int		j = -12;
	int		k = 123456789;
	int		l = 0;
	int		m = -12345678;
	char	*n = "abcdefghijklmnop";
	char	*o = "-a";
	char	*p = "-12";
	char	*q = "0";
	char	*r = "%%";
	char	*s = "-2147483648";
	char	*t = "0x12345678";
	char	*u = "-0";

	ft_printf("%u, %x, %X, %u, %x, %X, %u, %x, %X, %u, %x, %X, %u, %x, %X, %u, %x, %X, %u, %x, %X, %u, %x, %X", i, i, i, j, j, j, k, k, k, l, l, l, m, m, m, c, c, c, d, d, d, e, e, e);
} */