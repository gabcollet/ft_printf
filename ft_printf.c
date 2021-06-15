/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 12:05:56 by gcollet           #+#    #+#             */
/*   Updated: 2021/06/15 17:56:15 by gcollet          ###   ########.fr       */
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

char *ft_convert(unsigned int num, int base, int maj)
{
	static char	val[] = "0123456789abcdef";
	static char buffer[50];
	char *ptr;
	
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
		if (*format == '0')
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
			if (!(is_a_conversion_specifier(format)))
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

int ft_print_dori(int i, int ret, t_flags flags)
{
	int digit;
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
	if (flags.minus == 1)
	{
		if (i < 0)
		{
			digit++;
			i = -i;
			ret = ft_putchar('-', ret);
		}
	}
	if ((flags.minus == 0) && (flags.precision != -1)) 
	{
		while (((flags.width - 1) > flags.precision) && (flags.width > digit))
		{
			flags.width--;
			if ((flags.zero == 1) && (flags.width <= flags.precision))
				ret = ft_putchar('0', ret);
			else
				ret = ft_putchar(' ', ret);
		}
	}
	if ((i < 0 && flags.zero == 1) || (i < 0 && flags.minus == 0))
	{
		i = -i;
		ret = ft_putchar('-', ret);
		flags.width--;
	}
	if (flags.precision == 0)
		return (ret);

	while (flags.precision > digit)
	{
		flags.precision--;
		flags.width--;
		ret = ft_putchar('0', ret);
	}
	if ((flags.minus == 1) ||(flags.precision != -1))
		ret = ft_putstr(ft_convert(i, 10, 0), ret);
	while (flags.width > digit)
	{
		flags.width--;
		if (flags.zero == 1)
			ret = ft_putchar('0', ret);
		else if (flags.zero == 0)
			ret = ft_putchar(' ', ret);
	}
	if ((flags.minus == 0) && (flags.precision == -1))
		ret = ft_putstr(ft_convert(i, 10, 0), ret);
	return(ret);
}

int ft_printf(const char *format, ...)
{
	t_flags flags;
	int ret;

	ret = 0;
	va_list ap;
	va_start(ap, format); //Read strings and argument
	while (*format != '\0')
	{
		while(*format != '%' && *format != '\0') //If there is text print text until find the %
		{
			ret = ft_putchar(*format, ret);
			format++;
		}
		if (*format == '\0')
			break;
		format++; //Move to next character
		flags = ft_initialize_flag(flags); //Clear flags
		flags = ft_check(format, flags); //Check for flags, width and precision
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
				if (flags.width < 0)
				{
					flags.width = -flags.width;
					flags.minus = 1;
				}
		}
		while (!(is_a_conversion_specifier(format))) //Move to the specifier
			format++;
//Identify format specifier
//Take argument
//Do calculation according to the format specifier
//Convert result in string
//Print string
		if(*format == 'c')
			ret = ft_print_c(va_arg(ap, int), ret, flags);
		else if(*format == 'd' || *format == 'i')
			ret = ft_print_dori(va_arg(ap, int), ret, flags);
		else if(*format == 's')
			ret = ft_putstr(va_arg(ap, char *), ret);
		else if(*format == 'p')
		{
			ret = ft_putstr("0x10", ret);
			ret = ft_putstr(ft_convert(va_arg(ap, unsigned int), 16, 0), ret);
		}
		else if(*format == 'u')
			ret = ft_putstr(ft_convert(va_arg(ap, unsigned int), 10, 0), ret);
		else if(*format == 'x')
			ret = ft_putstr(ft_convert(va_arg(ap, unsigned int), 16, 0), ret);
		else if(*format == 'X')
			ret = ft_putstr(ft_convert(va_arg(ap, unsigned int), 16, 1), ret);
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
	ret = ft_printf(" 0*%0-*d*0 0*%0*d*0 ", 21, 1021, 21, -1011);
	printf("\n============================================================\n");
	retp = printf(" 0*%0-*d*0 0*%0*d*0 ", 21, 1021, 21, -1011);
	printf("\n#char imprimé ft_printf: %d\n", ret);
	printf("#char imprimé printf: %d\n", retp);
	return 0;
} */