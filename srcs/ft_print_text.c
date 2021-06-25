/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_text.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 12:09:37 by gcollet           #+#    #+#             */
/*   Updated: 2021/06/25 12:09:45 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

t_s	ft_print_text(t_s s)
{
	while (*s.format != '%' && *s.format != '\0')
	{
		s.ret = ft_putchar(*s.format, s.ret);
		s.format++;
	}
	return (s);
}
