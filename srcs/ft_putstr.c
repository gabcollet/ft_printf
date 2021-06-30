/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 12:17:18 by gcollet           #+#    #+#             */
/*   Updated: 2021/06/30 14:34:22 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_putstr(char *s, int ret)
{
	while (*s)
	{
		ret = ft_putchar(*s, ret);
		s++;
	}
	return (ret);
}

int	ft_putwstr(wchar_t *s, int ret)
{
	while (*s)
	{
		ret = ft_putwchar(*s, ret);
		s++;
	}
	return (ret);
}
