/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 12:05:56 by gcollet           #+#    #+#             */
/*   Updated: 2021/06/30 10:13:18 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

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
		s = ft_asterisk(ap, s);
		s = ft_length_format(ap, s);
		if (s.len == -1)
			return (s.ret);
		s.format++;
	}
	va_end(ap);
	return (s.ret);
}
