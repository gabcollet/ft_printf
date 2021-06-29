/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_wc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 11:14:18 by gcollet           #+#    #+#             */
/*   Updated: 2021/06/29 11:44:41 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_print_wc(wint_t c, t_s s)
{
	if (s.minus == 1)
		s.ret = ft_putwchar(c, s.ret);
	while (s.width > 1)
	{
		s.width--;
		if (s.zero == 1)
			s.ret = ft_putwchar('0', s.ret);
		else
			s.ret = ft_putwchar(' ', s.ret);
	}
	if (s.minus == 0)
		s.ret = ft_putwchar(c, s.ret);
	return (s.ret);
}
