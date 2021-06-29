/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ws.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 14:41:55 by gcollet           #+#    #+#             */
/*   Updated: 2021/06/29 15:46:26 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

t_s	ft_print_ws1(t_s s)
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
		s.ret = ft_putwstr(s.wptr, s.ret);
	if (s.precision > 0)
	{
		while (s.precision > 0 && s.wptr[0])
		{
			s.ret = ft_putwchar(s.wptr[0], s.ret);
			s.wptr++;
			s.precision--;
		}
	}
	return (s);
}

t_s	ft_print_ws2(t_s s)
{
	while ((++s.temp) < s.len && (s.precision > 0))
	{
		if ((s.width != 0) && (s.minus != 1))
			s.ret = ft_putchar(' ', s.ret);
	}
	if (s.precision > 0)
	{
		while (s.precision > 0 && s.wptr[0])
		{
			s.ret = ft_putwchar(s.wptr[0], s.ret);
			s.wptr++;
			s.precision--;
			s.width--;
		}
	}
	else if (s.precision != 0)
	{
		s.ret = ft_putwstr(s.wptr, s.ret);
		s.width -= s.len;
	}
	while (--s.width + 1 > 0)
		s.ret = ft_putchar(' ', s.ret);
	return (s);
}

int	ft_print_ws(wchar_t *wptr, t_s s)
{
	s.temp = s.precision;
	if (wptr == NULL)
		wptr = (wchar_t *)"(null)";
	s.wptr = wptr;
	s.len = ft_wstrlen(wptr);
	if ((s.width > 0) && (s.minus == 0))
		s = ft_print_ws1(s);
	else
		s = ft_print_ws2(s);
	return (s.ret);
}
