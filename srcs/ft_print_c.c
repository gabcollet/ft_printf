/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_c.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 11:07:00 by gcollet           #+#    #+#             */
/*   Updated: 2021/06/25 16:57:36 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_print_c(char c, t_s s)
{
	if (s.minus == 1)
		s.ret = ft_putchar(c, s.ret);
	while (s.width > 1)
	{
		s.width--;
		if (s.zero == 1)
			s.ret = ft_putchar('0', s.ret);
		else	
			s.ret = ft_putchar(' ', s.ret);
	}
	if (s.minus == 0)
		s.ret = ft_putchar(c, s.ret);
	return (s.ret);
}
