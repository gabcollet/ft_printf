/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_p.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 12:00:13 by gcollet           #+#    #+#             */
/*   Updated: 2021/06/25 12:02:53 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_print_p(char *ptr, t_s s)
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
