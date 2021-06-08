/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 12:05:56 by gcollet           #+#    #+#             */
/*   Updated: 2021/06/08 14:33:01 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdio.h>
#include "libft/ft_strlen.c"
#include "libft/ft_strlcpy.c"

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

int ft_printf(const char *format, ...)
{
	unsigned int i;
	char *s;
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

//Identify format specifier
//Take argument
//Do calculation according to the format specifier
//Convert result in string
//Print string
		
		if(*format == 'c')
		{
			i = va_arg(ap, int);
			ret = ft_putchar(i, ret);
		}
		else if(*format == 's')
		{
			s = va_arg(ap, char *);
			ret = ft_putstr(s, ret);
		}
		else if(*format == 'p')
		{
			i = va_arg(ap, unsigned int);
			ret = ft_putstr("0x10", ret);
			ret = ft_putstr(ft_convert(i, 16, 0), ret);
		}
		else if(*format == 'd' || *format == 'i')
		{
			i = va_arg(ap, int);
			if (i < 0)
			{
				i = -i;
				ret = ft_putchar('-', ret);

			}
			ret = ft_putstr(ft_convert(i, 10, 0), ret);
		}
		else if(*format == 'u')
		{
			i = va_arg(ap, unsigned int);
			ret = ft_putstr(ft_convert(i, 10, 0), ret);
		}
		else if(*format == 'x')
		{
			i = va_arg(ap, unsigned int);
			ret = ft_putstr(ft_convert(i, 16, 0), ret);
		}
		else if(*format == 'X')
		{
			i = va_arg(ap, unsigned int);
			ret = ft_putstr(ft_convert(i, 16, 1), ret);
		}
		else if(*format == '%')
		{
			ret = ft_putchar('%', ret);
		}
		format++;
	}
	va_end(ap);
	return(ret);
}

int main()
{
	int ret = 0;
	ret = ft_printf("", 2147483647);
	printf("\n============================================================\n");
	printf("", 2147483647);
	printf("\n%d", ret);
	return 0;
}